/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:23:09 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/11 17:50:47 by ykawakit         ###   ########.fr       */
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
		return (" ");
	if (start >= ft_strlen(s) || end > ft_strlen(s))
		return (" ");
	len = end - start - 1;
	if (s[end] != '\0')
		len = len - 1;
	sub = (char *) malloc ((ft_strlen(s) - len + 1) * sizeof(char));
	if (sub == 0)
		return (" ");
	i = -1;
	while (++i < start)
		sub[i] = s[i];
	j = 0;
	while (s[j + end] != '\0')
		sub[i++] = s[j++ + end];
	sub[i++] = ' ';
	sub[i] = '\0';
	return (sub);
}

// checks if quotes are all balanced, if not will return 0
int	balance_quotes(char *str)
{
	int	*in_quotes;
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	in_quotes = parse_quotes(str);
	while (str[i] != '\0')
	{
		if (in_quotes[i] == 3)
			ret++;
		i++;
	}
	free (in_quotes);
	if (ret % 2 == 0)
		return (1);
	return (0);
}

// checks if parenthesis are all balanced, if not will return 0
int	balance_para(char *str, int *in_quotes)
{
	int	op;
	int	cp;
	int	i;

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

// check balance of () and quotes
int	balance_pandq(char *str)
{
	int	ret;
	int	*in_quotes;

	in_quotes = parse_quotes(str);
	ret = 1;
	if (balance_quotes(str) == 0)
		ret = 0;
	if (balance_para(str, in_quotes) == -1)
		ret = 0;
	if (ret == 0)
		ft_printf("Parsing error! Check your quotes and/or parentheses!\n");
	free (in_quotes);
	return (ret);
}
