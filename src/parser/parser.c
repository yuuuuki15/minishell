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

char	**clean_quotes(char **tab)
{
	int	i;

	i = 0;
	ft_printf("Sent to cleaners\n");
	while (tab[i] != NULL)
	{
		if (tab[i][0] == '\'')
		{
			ft_printf("cleaning single quotes\n");
			tab[i] = ft_strtrim(tab[i], "\'");
		}
		else if (tab[i][0] == '\"')
		{
			ft_printf("cleaning double quotes\n");
			tab[i] = ft_strtrim(tab[i], "\"");
		}
		i++;
	}
	return (tab);
}

// store all commands in command structures
t_cmd	*parsecmd(char *str, t_tok *tok)
{
	t_cmd		*ret;
	t_execcmd	*cmd;
	char		*substr;
	t_tok		tok2;

	if (tok->tok == -1)
	{
		ret = make_execcmd();
		cmd = (t_execcmd *)ret;
		cmd->argv = clean_quotes(p_spliter(str)); //ft_split(str, ' ');
	}
	if (tok->tok == AND)
	{
		str = ft_strtrim(str, "&");
		get_token(&tok2, str);
		ret = make_backcmd(parsecmd(str, &tok2));
	}
	if (ft_tofile(tok->tok) == 1)
	{
		substr = ft_delstr(str, tok->s_loc, tok->cut);
		get_token(&tok2, substr);
		ret = make_redircmd(parsecmd(substr, &tok2), tok->str, tok->tok);
		free (substr);
	}
	return (ret);
}

void	get_token(t_tok *tok, char *str)
{
	int		ret;
	int		i;
	int		size;
	int		*q_check;

	ret = 0;
	i = 0;
	q_check = parse_quotes(str);
	while (str[i] != '\0' && (ft_isspace(str[i]) || !(ft_issym(str[i]) != -1 && q_check[i] == 0)))
		i++;
	tok->s_loc = i;
	if (ft_issym(str[i]) != RIN && ft_issym(str[i]) != ROUT)
		ret = ft_issym(str[i]);
	else
	{
		size = 1;
		if (ft_issym(str[i]) == RIN && ft_issym(str[i + 1]) == RIN)
		{
			i++;
			ret = RHERE;
			size++;
		}
		else if (ft_issym(str[i]) == RIN && ft_issym(str[i + 1]) != RIN)
			ret = RIN;
		else if (ft_issym(str[i]) == ROUT && ft_issym(str[i + 1]) != ROUT)
			ret = ROUT;
		else if (ft_issym(str[i]) == ROUT && ft_issym(str[i + 1]) == ROUT)
		{
			ret = ROUTA;
			i++;
			size++;
		}
		i++;
		tok->len = 0;
		while (str[i] != '\0' && (ft_isspace(str[i]) || ft_issym(str[i]) == -1))
		{
			tok->len++;
			i++;
		}
		tok->str = ft_strtrim(ft_substr(str, tok->s_loc + size, tok->len), " ");
		tok->size = tok->len + size - 1;
		tok->cut = i;
		ft_printf("file name for redirect: .%s.\n", tok->str);
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
		tok->quote = ft_substr(str, tok->s_loc, tok->len);
	}
	tok->tok = ret;
	free (q_check);
}

// locates a pipe if it is not in quotes
int	is_pipe(char *str, t_tok *tok)
{
	int	i;
	int	*q_check;

	q_check = parse_quotes(str);
	i = 0;
	while (str[i] != '\0' && !(str[i] == '|' && q_check[i] == 0))
		i++;
	free (q_check);
	if (i < (int)ft_strlen(str))
	{
		tok->s_loc = i + 1;
		tok->tok = PIP;
		tok->len = (int)ft_strlen(str) - (i + 1);
		return (1);
	}
	return (0);
}

// trims string so it only contains stuff after the pipe
char	*after_pipe(char *str, t_tok *tok)
{
	char	*next_cmd;

	next_cmd = ft_substr(str, tok->s_loc, tok->len);
	return (next_cmd);
}

// splits commands into pipe structure
t_cmd	*parse_pipe(char *str, t_tok *tok)
{
	t_cmd		*ret;
	char		*s_left;
	char		*s_right;
	t_tok		tok_right;

	s_left = ft_substr(str, 0, tok->s_loc - 1);
	s_right = after_pipe(str, tok);
	get_token(tok, s_left);
	if (is_pipe(s_right, &tok_right) == 1)
		ret = make_pipecmd(parsecmd(s_left, tok), parse_pipe(s_right, &tok_right));
	else
	{
		get_token(&tok_right, s_right);
		ret = make_pipecmd(parsecmd(s_left, tok), parsecmd(s_right, &tok_right));
	}
	free (s_left);
	free (s_right);
	return (ret);
}

// makes an integer array that denotes if in quotes
int	*parse_quotes(char *str)
{
	int	*in_quotes;
	int	i;
	int	sq_tok;
	int	dq_tok;

	in_quotes = (int *) malloc ((ft_strlen(str) + 1) * sizeof(int));
	if (in_quotes == 0)
		return (NULL);
	i = 0;
	sq_tok = 0;
	dq_tok = 0;
	while (str[i] != '\0')
	{
		if (ft_issym(str[i]) == SQ && dq_tok % 2 == 0)
			sq_tok++;
		if (ft_issym(str[i]) == DQ && sq_tok % 2 == 0)
			dq_tok++;
		if (dq_tok % 2 != 0 || sq_tok % 2 != 0 || ft_issym(str[i]) == SQ || ft_issym(str[i]) == DQ)
			in_quotes[i] = 1;
		else
			in_quotes[i] = 0;
		i++;
	}
	return (in_quotes);
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
	if (is_pipe(str, &tok) == 1)
	{
		cmd = parse_pipe(str, &tok);
	}
	else
	{
		get_token(&tok, str);
		cmd = parsecmd(str, &tok);
	}
	print_tree(cmd);
	return (cmd);
}
