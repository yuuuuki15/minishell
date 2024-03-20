/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_andor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:44:44 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/11 17:54:04 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// trims string so it only contains stuff after the ifand, to the right
char	*after_token(char *str, t_tok *tok)
{
	char	*next_cmd;

	next_cmd = ft_substr(str, tok->s_loc + tok->size - 1, tok->len);
	return (next_cmd);
}

// gets the type, important for & versus &&
int	get_type(char *str, t_tok *tok)
{
	char	*temp;
	char	*s_right;
	int		type;

	s_right = after_token(str, tok);
	temp = ft_strtrim(s_right, " ");
	if (tok->tok == AND && ft_strlen(temp) > 0)
		type = IFTHEN;
	else
		type = tok->tok;
	free (s_right);
	free (temp);
	return (type);
}

// splits commands into list structure if && or || is between two commands
t_cmd	*parse_ifthen(char *str, t_tok *tok, t_shell *shell)
{
	t_cmd		*ret;
	char		*s_left;
	char		*s_right;
	t_tok		tok_right;
	int			type;

	s_left = ft_substr(str, 0, tok->s_loc - 1);
	s_right = after_token(str, tok);
	type = get_type(str, tok);
	if (has_first_level(s_right, &tok_right) == 1)
		ret = make_listcmd(lexer(s_left, shell),
				parse_ifthen(s_right, &tok_right, shell), type);
	else if (type == BACK)
		ret = make_backcmd(lexer(s_left, shell));
	else
		ret = make_listcmd(lexer(s_left, shell), lexer(s_right, shell), type);
	free (s_left);
	free (s_right);
	return (ret);
}
