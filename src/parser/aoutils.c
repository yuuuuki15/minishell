/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aoutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:15:44 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:41:26 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Locates the first occurrence of || not within quotes or parentheses.
 * @param str char*: The input string to search.
 * @param tok t_tok*: Token structure to update with location and type.
 * @param q_check int*: Array indicating if a character is within quotes.
 * @param p_check int*: Array indicating if a character is within parentheses.
 * @return int: The index of the first || occurrence, or -1 if not found.
 */
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

/**
 * Locates the first occurrence of && or & not within quotes or parentheses.
 * @param str char*: The input string to search.
 * @param tok t_tok*: Token structure to update with location and type.
 * @param q_check int*: Array indicating if a character is within quotes.
 * @param p_check int*: Array indicating if a character is within parentheses.
 * @return int: The index of the first && or & occurrence, or -1 if not found.
 */
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

/**
 * Determines if a string contains first-level logical operators.
 * @param str char*: The input string to search.
 * @param tok t_tok*: Token structure to update with found operator info.
 * @return int: 1 if a first-level operator is found, 0 otherwise.
 * @note This function updates tok only if a first-level operator is found.
 */
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
