/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:44:44 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/07 13:45:01 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// locates && if not in quotes
int	is_ifthen(char *str, t_tok *tok)
{
	int	i;
	int	*q_check;

	q_check = parse_quotes(str);
	i = 0;
	while (str[i] != '\0' && !(str[i] == '&' && q_check[i] == 0))
		i++;
	free (q_check);
	if (i < (int)ft_strlen(str) && str[i + 1] == '&')
	{
		tok->s_loc = i + 1;
		tok->tok = IFTHEN;
		tok->size = 2;
		tok->len = (int)ft_strlen(str) - (tok->s_loc + tok->size - 1);
		return (i + 1);
	}
	return (-1);
}

// locates || if not in quotes
int	is_ifor(char *str, t_tok *tok)
{
	int	i;
	int	*q_check;

	q_check = parse_quotes(str);
	i = 0;
	while (str[i] != '\0' && !(str[i] == '|' && q_check[i] == 0))
		i++;
	free (q_check);
	if (i < (int)ft_strlen(str) && str[i + 1] == '|')
	{
		tok->s_loc = i + 1;
		tok->tok = IFOR;
		tok->size = 2;
		tok->len = (int)ft_strlen(str) - (tok->s_loc + tok->size - 1);
		return (i + 1);
	}
	return (-1);
}

// trims string so it only contains stuff after the ifand, to the right
char	*after_token(char *str, t_tok *tok)
{
	char	*next_cmd;

	next_cmd = ft_substr(str, tok->s_loc + tok->size - 1, tok->len);
	return (next_cmd);
}

// splits commands into list structure if && is between two commands
t_cmd	*parse_ifthen(char *str, t_tok *tok)
{
	t_cmd		*ret;
	char		*s_left;
	char		*s_right;
	t_tok		tok_right;
	t_tok		tok2;
	int			type;

	s_left = ft_substr(str, 0, tok->s_loc - 1);
	s_right = after_token(str, tok);
	type = tok->tok;
	get_token(tok, s_left);
	if (is_ifthen(s_right, &tok_right) != -1 || is_ifor(s_right, &tok2) != -1)
	{
		if (tok_right.s_loc < tok2.s_loc)
			ret = make_listcmd(parsecmd(s_left, tok),
					parse_ifthen(s_right, &tok_right), tok_right.tok);
		else
			ret = make_listcmd(parsecmd(s_left, tok),
					parse_ifthen(s_right, &tok_right), tok2.tok);
	}
	else
	{
		get_token(&tok_right, s_right);
		ret = make_listcmd(parsecmd(s_left, tok),
				parsecmd(s_right, &tok_right), type);
	}
	free (s_left);
	free (s_right);
	return (ret);
}
