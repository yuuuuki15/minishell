/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:34:01 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/04 09:23:40 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// use readline to display prompt and read in user input
// treat "exit" and ctrl-D but only when alone on line
// add non-blank lines to history
int	get_data(void)
{
	if (g_shell->user_input || g_shell->sig == 0)
	{
		free (g_shell->user_input);
		g_shell->user_input = NULL;
		g_shell->sig = 1;
	}
	g_shell->user_input = readline(PROMPT);
	if (!g_shell->user_input || ft_strcmp(g_shell->user_input, "exit") == 0)
	{
		free (g_shell->user_input);
		// need to free all open structures, need a tree cleaning alg
		clear_history();
		ft_printf("%s", "Exiting shell\n");
		exit(0);
	}
	if (ft_strlen(g_shell->user_input) > 0)
		add_history(g_shell->user_input);
	if (ft_strcmp(g_shell->user_input, "") == 0
		|| ft_strisspace(g_shell->user_input))
		return (0);
	else
	{
		if (g_shell->sig == 1)
		{
			ft_print_line(g_shell->user_input);
			return (1);
		}
		else
			return (0);
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
		//ft_printf("in pipe left: %s, right: %s\n", s_left, s_right);
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
	if (ft_issym(str[i]) != RINPUT && ft_issym(str[i]) != LT)
		ret = ft_issym(str[i]);
	else
	{
		if (ft_issym(str[i]) == RINPUT && ft_issym(str[i + 1]) == RINPUT)
		{
			i++;
			ret = DGT;
		}
		else if (ft_issym(str[i]) == RINPUT && ft_issym(str[i + 1]) != RINPUT)
			ret = RINPUT;
		else if (ft_issym(str[i]) == LT && ft_issym(str[i + 1]) != LT)
			ret = LT;
		else if (ft_issym(str[i]) == LT && ft_issym(str[i + 1]) == LT)
		{
			ret = DLT;
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
		//ft_printf("about to look for second quote: %d %c\n", i, str[i]); 
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

t_cmd	*lexer(char *str)
{
	t_cmd		*cmd;
	t_backcmd	*bcmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;
	t_tok		tok;

	if (str == NULL || g_shell->sig == 0)
		return (NULL);
	get_token(&tok, str);
	//if (tok.tok != DQ && tok.tok != SQ)
		//ft_printf("tok: %d at %d\n", tok.tok, tok.s_loc);
	//else
	//	ft_printf("found quotes from %d (len %d), forming string: %s\n", tok.s_loc, tok.len, tok.str);
	ft_printf("before parser: %s\n", str);
	cmd = parsecmd(str, &tok);
	if (cmd->type == EXEC)
	{
		//ft_printf("after parser: ");
		printcmd(cmd);
	}
	if (cmd->type == BACK)
	{
		//ft_printf("after parser: ");
		bcmd = (t_backcmd *)cmd;
		printcmd(bcmd->cmd);
	}
	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		//ft_printf("after parser:\n");
		//ft_printf("left command: ");
		printcmd(pcmd->left);
		//ft_printf("right command: ");
		printcmd(pcmd->right);
	}
	if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		//ft_printf("after parser:\n");
		printcmd(rcmd->cmd);
		printf("file: %s, mode: %d\n", rcmd->file, rcmd->mode);
	}
	return (cmd);
}
