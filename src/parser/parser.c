/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:34:01 by mevonuk           #+#    #+#             */
/*   Updated: 2024/02/27 13:19:12 by ykawakit         ###   ########.fr       */
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
	if (shell->user_input == NULL) //ctrl-D
	{
		free (shell->user_input);
			clear_history();
			ft_printf("%s", "\nExiting shell\n");
			exit(0);
	}
	else
	{
		if (ft_strlen(shell->user_input) > 0)
			add_history(shell->user_input);
		if (ft_strcmp(shell->user_input, "exit") == 0)
		{
			free (shell->user_input);
			clear_history();
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
	}
	return (0);
}

t_cmd	*parsecmd(char *str, t_tok *tok)
{
	t_cmd		*ret;
	t_execcmd	*cmd;
	t_backcmd	*bcmd;
    //t_pipecmd   *pcmd;
    //char        *s_left;
    //char        *s_right;

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
    // if (tok->tok == PIP)
    // {
        // s_left = ft_substr(str, 0, tok->i);
        // s_right = ft_substr(str, tok->i + 1, (int)ft_strlen(str) - tok->i);
        // ret = make_pipecmd(s_left, s_right);
        // pcmd = (t_pipecmd *)ret;
    // }
	return (ret);
}

void	printcmd(t_cmd *cmd)
{
	int			i;
	t_execcmd	*out;

	out = (t_execcmd *)cmd;
	ft_printf("after parser: ");
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
	st = s;
	tok->tok = ret;
    tok->i = i;
}

t_cmd	*lexer(char *str)
{
	t_cmd		*cmd;
	char		*st;
	char		*et;
	t_backcmd	*bcmd;
    t_tok       tok;

	if (str == NULL)
		return (NULL);
	st = str;
	et = str + ft_strlen(str) - 1;
	get_token(&tok, st, et);
	// printf("tok: %d at %d\n", tok.tok, tok.i);
	printf("before parser: %s\n", str);
	cmd = parsecmd(str, &tok);
	if (cmd->type == EXEC)
		printcmd(cmd);
	if (cmd->type == BACK)
	{
		bcmd = (t_backcmd *)cmd;
		printcmd(bcmd->cmd);
	}
	return (cmd);
}
