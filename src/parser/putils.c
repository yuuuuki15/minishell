/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:23:09 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/06 10:41:19 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks if string is all spaces
int	ft_strisspace(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	if (i < (int)ft_strlen(line))
		return (0);
	else
		return (1);
}

// deletes a sub string from a string specifying start and end
char	*ft_delstr(char const *s, unsigned int start, unsigned int end)
{
	char			*sub;
	unsigned int	i;
	unsigned int	len;
	unsigned int	j;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s) || end > ft_strlen(s))
		return (NULL);
	len = end - start - 1;
	if (s[end] != '\0')
		len = len - 1;
	sub = (char *) malloc ((ft_strlen(s) - len + 1) * sizeof(char));
	if (sub == 0)
		return (NULL);
	i = -1;
	while (++i < start)
		sub[i] = s[i];
	j = 0;
	while (s[j + end] != '\0')
		sub[i++] = s[j++ + end];
	sub[i] = '\0';
	return (sub);
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

// checks if parenthesis are all balanced, if not will return 0
int	balance_para(char *str)
{
	int	op;
	int	cp;
	int	i;
	int	*in_quotes;

	in_quotes = parse_quotes(str);
	i = 0;
	op = 0;
	cp = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(' && in_quotes[i] == 0)
			op++;
		if (str[i] == ')' && in_quotes[i] == 0)
			cp++;
		if (cp > op)
			return (0);
		i++;
	}
	if (op != cp)
		return (-1);
	return (op);
}
