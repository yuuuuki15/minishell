/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:06:15 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 11:15:52 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks if char is space character
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

// checks if token is a redirect
int	ft_tofile(int tok)
{
	if (tok == RIN || tok == ROUT || tok == ROUTA || tok == RHERE)
		return (1);
	return (0);
}

// checks if char is a token, not including quotes but including parentheses
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

// checks if char is a token, not including quotes but including parentheses
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

// characters allowed in a variable name
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
