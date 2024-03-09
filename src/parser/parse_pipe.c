/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:20:25 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/09 15:41:54 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// trims string so it only contains stuff after the pipe, to the right
char	*after_pipe(char *str, t_tok *tok)
{
	char	*next_cmd;

	next_cmd = ft_substr(str, tok->s_loc, tok->len);
	return (next_cmd);
}

// splits commands into pipe structure
t_cmd	*parse_pipe(char *str, t_tok *tok, t_shell *g_shell)
{
	t_cmd		*ret;
	char		*s_left;
	char		*s_right;
	t_tok		tok_right;

	s_left = ft_substr(str, 0, tok->s_loc - 1);
	s_right = after_pipe(str, tok);
	get_token(tok, s_left);
	if (is_pipe(s_right, &tok_right) == 1)
		ret = make_listcmd(parsecmd(s_left, tok, g_shell),
				parse_pipe(s_right, &tok_right, g_shell), PIPE);
	else
	{
		get_token(&tok_right, s_right);
		ret = make_listcmd(parsecmd(s_left, tok, g_shell),
				parsecmd(s_right, &tok_right, g_shell), PIPE);
	}
	free (s_left);
	free (s_right);
	return (ret);
}
