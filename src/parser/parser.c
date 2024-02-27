/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:34:01 by mevonuk           #+#    #+#             */
/*   Updated: 2024/02/27 11:22:53 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// use readline to display prompt and read in user input
// treat "exit" and spaces
// add non-blank lines to history
int	get_data(t_shell *shell)
{
	if (shell->user_input)
	{
		free (shell->user_input);
		shell->user_input = NULL;
	}
	shell->user_input = readline(PROMPT);
	if (ft_strlen(shell->user_input) > 0)
		add_history(shell->user_input);
	if (ft_strcmp(shell->user_input, "exit") == 0)
	{
		free (shell->user_input);
		rl_clear_history();
		ft_printf("%s", "Exiting shell\n");
		exit(0);
	}
	if (ft_strcmp(shell->user_input, "") == 0
		|| ft_strisspace(shell->user_input))
		handle_space();
	else
	{
		ft_print_line(shell->user_input);
		return (1);
	}
	return (0);
}

t_cmd	*parsecmd(char *str, t_tok *tok)
{
	t_cmd		*ret;
	t_execcmd	*cmd;
	t_backcmd	*bcmd;
    t_pipecmd   *pcmd;
    char        *s_left;
    char        *s_right;

	if (tok->tok == -1)
	{
		ret = make_execcmd();
		cmd = (t_execcmd *)ret;
		cmd->argv = ft_split(str, ' ');
	}
	if (tok->tok== AND)
	{
		ret = make_backcmd();
		bcmd = (t_backcmd *)ret;
		str = ft_strtrim(str, "&");
		tok->tok = -1;
		bcmd->cmd = parsecmd(str, tok);
	}
    if (tok->tok == PIP)
    {
        s_left = ft_substr(str, 0, tok->s_loc);
        s_right = ft_substr(str, tok->s_loc + 1, (int)ft_strlen(str) - tok->s_loc);
		ft_printf("in pipe left: %s, right: %s\n", s_left, s_right);
		tok->tok = -1;
        ret = make_pipecmd(parsecmd(s_left, tok), parsecmd(s_right, tok));
        pcmd = (t_pipecmd *)ret;
    }
	return (ret);
}

void	printcmd(t_cmd *cmd)
{
	int			i;
	t_execcmd	*out;

	out = (t_execcmd *)cmd;
	i = 0;
	while (out->argv[i] != NULL)
	{
		ft_printf("%s ", out->argv[i]);
		i++;
	}
	ft_printf("\n");
}

void	get_token(t_tok *tok, char *st, char *et)
{
	char	*s;
	int		ret;
    int     i;

	s = st;
	ret = 0;
    i = 0;
	while (s < et && (ft_isspace(*s) || ft_issym(*s) == -1))
    {
        i++;
		s++;
    }
	ft_printf("current token read: %c\n", *s);
	if (ft_issym(*s) != GT && ft_issym(*s) != LT)
		ret = ft_issym(*s);
	else
	{
		if (ft_issym(*s) == GT && ft_issym(*++s) == GT)
			ret = DGT;
		else if (ft_issym(*s) == GT && ft_issym(*++s) != GT)
			ret = GT;
		else if (ft_issym(*s) == LT && ft_issym(*++s) != LT)
			ret = LT;
		else if (ft_issym(*s) == LT && ft_issym(*++s) == LT)
			ret = DLT;
	}
	tok->tok = ret;
    tok->s_loc = i;
	if (ret == SQ || ret == DQ)
	{
		i++;
		while (s < et && ft_issym(*s) != ret)
		{
			s++;
			i++;
		}
		if (s < et)
		{
			ft_printf("i %d s_loc %d \n", i, tok->s_loc);
			tok->len = i - tok->s_loc - 1;
			tok->inquote = ft_substr(st, tok->s_loc + 1, tok->len);
		}
		else
			ft_printf("Error: unbalanced quotes.\n");
	}
	st = s;
}

t_cmd	*lexer(char *str)
{
	t_cmd		*cmd;
	char		*st;
	char		*et;
	t_backcmd	*bcmd;
	t_pipecmd	*pcmd;
    t_tok       tok;

	if (str == NULL)
		return (NULL);
	st = str;
	et = str + ft_strlen(str) - 1;
	get_token(&tok, st, et);
	if (tok.tok != DQ && tok.tok != SQ)
		ft_printf("tok: %d at %d\n", tok.tok, tok.s_loc);
	else
		ft_printf("found quotes from %d (len %d), forming string: %s\n", tok.s_loc, tok.len, tok.inquote);
	ft_printf("before parser: %s\n", str);
	cmd = parsecmd(str, &tok);
	if (cmd->type == EXEC)
	{
		ft_printf("after parser: ");
		printcmd(cmd);
	}
	if (cmd->type == BACK)
	{
		ft_printf("after parser: ");
		bcmd = (t_backcmd *)cmd;
		printcmd(bcmd->cmd);
	}
	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		ft_printf("after parser:\n");
		ft_printf("left command: ");
		printcmd(pcmd->left);
		ft_printf("right command: ");
		printcmd(pcmd->right);
	}
	return (cmd);
}
