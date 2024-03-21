/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:06:15 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/21 12:26:22 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if a character is a space character.
 * @param c char: The character to check.
 * @return int: 1 if the character is a space, 0 otherwise.
 */
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

/**
 * Checks if a token represents a redirection.
 * @param tok int: The token to check.
 * @return int: 1 if the token is a redirection, 0 otherwise.
 */
int	ft_tofile(int tok)
{
	if (tok == RIN || tok == ROUT || tok == ROUTA || tok == RHERE)
		return (1);
	return (0);
}

/**
 * Checks if a character is a token, excluding quotes but including parentheses.
 * @param c char: The character to check.
 * @return int: Token type if the character is a token, -1 otherwise.
 */
int	ft_istok(char c)
{
	if (c == '<')
		return (RIN);
	if (c == '>')
		return (ROUT);
	if (c == '|')
		return (PIP);
	if (c == '&')
		return (AND);
	return (-1);
}

/**
 * Checks if a character sequence is a full token, excluding quotes but
 * including parentheses.
 * @param str char*: The string containing the character sequence.
 * @param i int: The index of the first character in the sequence.
 * @return int: Token type if the sequence is a full token, -1 otherwise.
 */
int	ft_isfulltok(char *str, int i)
{
	char	c1;
	char	c2;

	c1 = str[i];
	c2 = '\0';
	if (str[i + 1] != '\0')
		c2 = str[i + 1];
	if (c1 == '<' && c2 == '<')
		return (RHERE);
	if (c1 == '>' && c2 == '>')
		return (ROUTA);
	if (c1 == '|' && c2 == '|')
		return (IFOR);
	if (c1 == '&' && c2 == '&')
		return (IFTHEN);
	return (-1);
}

/**
 * Checks if a character is allowed in a variable name.
 * @param c char: The character to check.
 * @return int: 1 if the character is allowed, 0 otherwise.
 */
int	ft_isallowed(char c)
{
	if (ft_isalnum(c) == 1)
		return (1);
	if (c == '/')
		return (0);
	if (c == '_')
		return (1);
	return (0);
}
