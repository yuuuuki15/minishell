/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:07:43 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 11:34:05 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// expansion of lexer for line count
// deals with single commands, quotes, parentheses, and redirects
static t_cmd	*lexer_helper(char *str, t_shell *shell)
{
	t_cmd		*cmd;
	t_tok		tok;
	char		*strim;

	strim = ft_strtrim(str, " ");
	if (strim[0] == '(')
		cmd = parse_paren(strim, shell);
	else
	{
		get_token(&tok, strim);
		if (tok.tok == FERR)
		{
			free (strim);
			return (NULL);
		}
		cmd = parsecmd(strim, &tok, shell);
	}
	if (strim)
		free (strim);
	return (cmd);
}

// check for starting with pipe or and
int static	bad_pipe_and(char *str)
{
	char	*temp;

	temp = ft_strtrim(str, " ");
	if (temp[0] == '|' || temp[0] == '&')
	{
		ft_printf("unexpected token at \'%c\'\n", temp[0]);
		free (temp);
		return (1);
	}
	free (temp);
	return (0);
}

// checks if input is NULL
// checks if parenthesis and quotes are balanced
// parses command into simple "tree" based on tokens
// returns tree
t_cmd	*lexer(char *str, t_shell *shell)
{
	t_cmd		*cmd;
	t_tok		tok;

	if (str == NULL)
		return (NULL);
	if (balance_pandq(str) == 0)
		return (NULL);
	if (bad_pipe_and(str) != 0)
		return (NULL);
	if (has_first_level(str, &tok) == 1)
		cmd = parse_ifthen(str, &tok, shell);
	else if (is_pipe(str, &tok) == 1)
		cmd = parse_pipe(str, &tok, shell);
	else
		cmd = lexer_helper(str, shell);
	return (cmd);
}
