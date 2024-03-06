/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:18:48 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/06 10:51:52 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// mark the positions of quotes that need to be removed
int	*to_remove(int *in_quotes, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (i == 0 && in_quotes[i] == 1)
			in_quotes[i] = 2;
		if (i > 0 && in_quotes[i] == 1 && in_quotes[i - 1] == 0)
			in_quotes[i] = 2;
		if (i < len - 1 && in_quotes[i] == 1 && in_quotes[i + 1] == 0)
			in_quotes[i] = 2;
		if (i == len - 1 && in_quotes[i] == 1)
			in_quotes[i] = 2;
		i++;
	}
	return (in_quotes);
}

// trims paired quotes from string
char	*remove_quotes(char *str)
{
	int	*in_quotes;
	int	i;
	int	j;
	int	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	in_quotes = parse_quotes(str);
	in_quotes = to_remove(in_quotes, len);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (in_quotes[i] == 2)
			i++;
		else
		{
			str[j] = str[i];
			j++;
			i++;
		}
	}
	str[j] = '\0';
	return (str);
}

// checks if quotes are all balanced, if not will return 0
int	balance_quotes(char *str)
{
	int	sq_tok;
	int	dq_tok;
	int	i;

	i = 0;
	sq_tok = 0;
	dq_tok = 0;
	while (str[i] != '\0')
	{
		if (ft_issym(str[i]) == SQ && dq_tok % 2 == 0)
			sq_tok++;
		if (ft_issym(str[i]) == DQ && sq_tok % 2 == 0)
			dq_tok++;
		i++;
	}
	if (sq_tok % 2 == 0 && dq_tok % 2 == 0)
		return (1);
	return (0);
}

// makes an integer array that denotes if in quotes
int	*parse_quotes(char *str)
{
	int	*in_quotes;
	int	i;
	int	sq_tok;
	int	dq_tok;

	in_quotes = (int *) malloc ((ft_strlen(str) + 1) * sizeof(int));
	if (in_quotes == 0)
		return (NULL);
	i = 0;
	sq_tok = 0;
	dq_tok = 0;
	while (str[i] != '\0')
	{
		if (ft_issym(str[i]) == SQ && dq_tok % 2 == 0)
			sq_tok++;
		if (ft_issym(str[i]) == DQ && sq_tok % 2 == 0)
			dq_tok++;
		if (dq_tok % 2 != 0 || sq_tok % 2 != 0
			|| ft_issym(str[i]) == SQ || ft_issym(str[i]) == DQ)
			in_quotes[i] = 1;
		else
			in_quotes[i] = 0;
		i++;
	}
	return (in_quotes);
}
