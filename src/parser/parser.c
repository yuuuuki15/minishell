/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:34:01 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/04 11:59:52 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exiting shell, free global variable
// should also free tree! Add this.
void	exit_shell(void)
{
	free (g_shell->user_input);
	rl_clear_history();
	ft_printf("%s", "Exiting shell\n");
	exit(0);
}

// use readline to display prompt and read in user input
// treat "exit" and ctrl-D but only when alone on line
// add non-blank lines to history
int	get_data(void)
{
	if (g_shell->user_input)
	{
		free (g_shell->user_input);
		g_shell->user_input = NULL;
	}
	g_shell->user_input = readline(PROMPT);
	if (!g_shell->user_input || ft_strcmp(g_shell->user_input, "exit") == 0)
	{
		if (!g_shell->user_input)
			ft_printf("Exiting due to NULL input\n");
		if (ft_strcmp(g_shell->user_input, "exit") == 0)
			ft_printf("exiting due to exit command\n");
		exit_shell();
	}
	if (ft_strlen(g_shell->user_input) > 0)
		add_history(g_shell->user_input);
	if (ft_strcmp(g_shell->user_input, "") == 0
		|| ft_strisspace(g_shell->user_input))
		return (0);
	else
	{
		ft_print_line(g_shell->user_input);
		return (1);
	}
	return (0);
}

t_cmd	*parsecmd(char *str, t_tok *tok)
{
	t_cmd		*ret;
	t_execcmd	*cmd;
	char		*s_left;
	char		*s_right;
	char		*substr;

	if (tok->tok == -1)
	{
		ret = make_execcmd();
		cmd = (t_execcmd *)ret;
		cmd->argv = ft_split(str, ' ');
	}
	if (tok->tok == AND)
	{
		str = ft_strtrim(str, "&");
		tok->tok = -1;
		ret = make_backcmd(parsecmd(str, tok));
	}
	if (tok->tok == PIP)
	{
		s_left = ft_substr(str, 0, tok->s_loc);
		s_right = ft_substr(str, tok->s_loc + 1,
				(int)ft_strlen(str) - tok->s_loc);
		tok->tok = -1;
		ret = make_pipecmd(parsecmd(s_left, tok), parsecmd(s_right, tok));
	}
	if (tok->tok == REDIR)
	{
		tok->tok = -1;
		substr = ft_delstr(str, tok->s_loc, tok->len);
		ft_printf("substr: %s\n", substr);
		ret = make_redircmd(parsecmd(substr, tok), tok->str, O_RDONLY, 0);
	}
	return (ret);
}

void	get_token(t_tok *tok, char *str)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (str[i] != '\0' && (ft_isspace(str[i]) || ft_issym(str[i]) == -1))
		i++;
	tok->s_loc = i;
	if (ft_issym(str[i]) != RIN && ft_issym(str[i]) != ROUT)
		ret = ft_issym(str[i]);
	else
	{
		if (ft_issym(str[i]) == RIN && ft_issym(str[i + 1]) == RIN)
		{
			i++;
			ret = RHERE;
		}
		else if (ft_issym(str[i]) == RIN && ft_issym(str[i + 1]) != RIN)
			ret = RIN;
		else if (ft_issym(str[i]) == ROUT && ft_issym(str[i + 1]) != ROUT)
			ret = ROUT;
		else if (ft_issym(str[i]) == ROUT && ft_issym(str[i + 1]) == ROUT)
		{
			ret = ROUTA;
			i++;
		}
		i++;
		tok->len = 0;
		while (str[i] != '\0' && (ft_isspace(str[i]) || ft_issym(str[i]) == -1))
		{
			tok->len++;
			i++;
		}
		tok->str = ft_strtrim(ft_substr(str, tok->s_loc + 1, tok->len), " ");
		ft_printf("file name for redirect: %s\n", tok->str);
	}
	if (ret == SQ || ret == DQ)
	{
		tok->s_loc++;
		i++;
		tok->len = 0;
		while (str[i] != '\0' && ft_issym(str[i]) != ret)
		{
			tok->len++;
			i++;
		}
		tok->str = ft_substr(str, tok->s_loc, tok->len);
	}
	tok->tok = ret;
}

int	count_tokens(char *str)
{
	int	n_tok;
	int	sq_tok;
	int	dq_tok;
	int	i;

	i = 0;
	n_tok = 0;
	sq_tok = 0;
	dq_tok = 0;
	while (str[i] != '\0')
	{
		if (ft_istok(str[i]) != -1)
		{
			ft_printf("found %c at %d\n", str[i], i);
			n_tok++;
		}
		i++;
	}
	ft_printf("Total number of tokens: %d\n", n_tok);
	return (n_tok);
}

int	is_pipe(char *str, t_tok *tok)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '|')
		i++;
	if (i < (int)ft_strlen(str))
	{
		tok->s_loc = i + 1;
		tok->tok = PIP;
		tok->len = (int)ft_strlen(str) - (i + 1);
		return (1);
	}
	return (0);
}

char	*after_pipe(char *str, t_tok *tok)
{
	char	*next_cmd;

	next_cmd = ft_substr(str, tok->s_loc, tok->len);
	ft_printf("remainder: %s\n", next_cmd);
	return (next_cmd);
}

int	find_redir(char *str, t_tok *tok)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isredir(str[i]) != -1)
		i++;
	if (ft_isredir(str[i]) != -1) //i < (int)ft_strlen(str))
	{
		i++;
		tok->len = 0;
		while (str[i] != '\0' && (ft_isspace(str[i]) || ft_issym(str[i]) == -1))
		{
			tok->len++;
			i++;
		}
		tok->str = ft_strtrim(ft_substr(str, tok->s_loc + 1, tok->len), " ");
		ft_printf("file name for redirect: %s\n", tok->str);
		return (1);
	}
	else
	{
		get_token(tok, str);
	}
	return (0);
}

t_cmd	*parse_pipe(char *str, t_tok *tok)
{
	t_cmd		*ret;
	char		*s_left;
	char		*s_right;
	t_tok		tok_right;

	s_left = ft_substr(str, 0, tok->s_loc - 1);
	s_right = after_pipe(str, tok);
	find_redir(s_left, tok);
	if (is_pipe(s_right, &tok_right) == 1)
		ret = make_pipecmd(parsecmd(s_left, tok), parse_pipe(s_right, &tok_right));
	else
	{
		find_redir(s_right, &tok_right);
		ret = make_pipecmd(parsecmd(s_left, tok), parsecmd(s_right, &tok_right));
	}
	return (ret);
}

// currently checks if input is NULL
// reads in first token and then parses command into simple "tree"
// prints tree and then returns tree
t_cmd	*lexer(char *str)
{
	t_cmd		*cmd;
	t_tok		tok;

	if (str == NULL)
		return (NULL);
	if (balance_quotes(str) == 0)
	{
		ft_printf("error: Unbalanced quotes!\n");
		return (NULL);
	}
	if (count_tokens(str) != 0)
	{
		if (is_pipe(str, &tok) == 1)
		{
			cmd = parse_pipe(str, &tok);
		}
		else
		{
			get_token(&tok, str);
			cmd = parsecmd(str, &tok);
		}
	}
	else
	{
		get_token(&tok, str);
		cmd = parsecmd(str, &tok);
	}
	print_tree(cmd);
	//get_token(&tok, str);
	cmd = NULL;
	//cmd = parsecmd(str, &tok);
	//print_tree(cmd);
	return (cmd);
}
