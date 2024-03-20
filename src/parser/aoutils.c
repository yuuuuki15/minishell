/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aoutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:15:44 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 11:36:00 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// locates || if not in quotes and not in ()
static int	is_ifor(char *str, t_tok *tok, int *q_check, int *p_check)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !(str[i] == '|'
			&& q_check[i] == 0 && p_check[i] == 0))
		i++;
	while (i < (int)ft_strlen(str))
	{
		if (i < (int)ft_strlen(str) && str[i] == '|' && str[i + 1] == '|')
		{
			tok->s_loc = i + 1;
			tok->tok = IFOR;
			tok->size = 2;
			tok->len = (int)ft_strlen(str) - (tok->s_loc + tok->size - 1);
			return (i + 1);
		}
		else
			i++;
	}
	return (-1);
}

// locates && and & if not in quotes and not in ()
static int	is_ifthen(char *str, t_tok *tok, int *q_check, int *p_check)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !(str[i] == '&'
			&& q_check[i] == 0 && p_check[i] == 0))
		i++;
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

int	has_first_level(char *str, t_tok *tok)
{
	t_tok	tok2;
	int		*p_check;
	int		ret;
	int		*q_check;

	q_check = parse_quotes(str);
	p_check = parse_para(str);
	ret = 0;
	if (is_ifthen(str, tok, q_check, p_check) != -1)
	{
		if (is_ifor(str, &tok2, q_check, p_check) != -1
			&& tok->s_loc > tok2.s_loc)
			is_ifor(str, tok, q_check, p_check);
		ret = 1;
	}
	if (is_ifor(str, tok, q_check, p_check) != -1)
		ret = 1;
	free (p_check);
	free (q_check);
	return (ret);
}
