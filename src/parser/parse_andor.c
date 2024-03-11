/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_andor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:44:44 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/10 17:43:04 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_first_level(char *str, t_tok *tok)
{
	t_tok	tok2;

	if (is_ifthen(str, tok) != -1)
	{
		if (is_ifor(str, &tok2) != -1 && tok->s_loc > tok2.s_loc)
		{
			is_ifor(str, tok);
			return (1);
		}
		else
			return (1);
	}
	if (is_ifor(str, tok) != -1)
		return (1);
	return (0);
}

// locates && and & if not in quotes
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
	if (i < (int)ft_strlen(str) && str[i + 1] != '&')
	{
		tok->s_loc = i + 1;
		tok->tok = AND;
		tok->size = 1;
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
	if (tok->tok == AND && ft_strlen(ft_strtrim(s_right, " ")) > 0)
		type = IFTHEN;
	else
		type = tok->tok;
	if (has_first_level(s_right, &tok_right) == 1)
		ret = make_listcmd(lexer(s_left, shell),
				parse_ifthen(s_right, &tok_right, shell), type);
	else
		ret = make_listcmd(lexer(s_left, shell), lexer(s_right, shell), type);
	free (s_left);
	free (s_right);
	return (ret);
}
