/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:23:09 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:51:08 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if a string consists only of spaces.
 * @param line char*: The string to check.
 * @return int: 1 if the string is all spaces, 0 otherwise.
 */
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

/**
 * Deletes a substring from a string by specifying start and end indices.
 * @param s char const*: The original string.
 * @param start unsigned int: The start index of the substring to delete.
 * @param end unsigned int: The end index of the substring to delete.
 * @return char*: The modified string without the specified substring.
 * @error Returns " " if s is NULL or indices are out of bounds.
 */
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

/**
 * Checks if quotes in a string are balanced.
 * @param str char*: The string to check.
 * @return int: 1 if quotes are balanced, 0 otherwise.
 */
static int	balance_quotes(char *str)
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

/**
 * Checks if parentheses in a string are balanced.
 * @param str char*: The string to check.
 * @param in_quotes int*: Array indicating if a character is within quotes.
 * @return int: The number of balanced parentheses pairs, -1 if unbalanced.
 */
static int	balance_para(char *str, int *in_quotes)
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

/**
 * Checks the balance of parentheses and quotes in a string.
 * @param str char*: The string to check.
 * @return int: 1 if both parentheses and quotes are balanced, 0 otherwise.
 * @error Prints an error message if unbalanced.
 */
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
		ft_putendl_fd("Unbalanced quotes and/or parentheses!", STDERR_FILENO);
	free (in_quotes);
	return (ret);
}
