/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:06:15 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/06 16:07:02 by mevonuk          ###   ########.fr       */
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

// checks if char is > or <
int	ft_isredir(char c)
{
	if (c == '<')
		return (RIN);
	if (c == '>')
		return (ROUT);
	return (-1);
}

// checks if token is a redirect
int	ft_tofile(int tok)
{
	if (tok == RIN || tok == ROUT || tok == ROUTA || tok == RHERE)
		return (1);
	return (0);
}

// checks if char is a token
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

// checks if char is a symbol
int	ft_issym(char c)
{
	if (c == '<')
		return (RIN);
	if (c == '>')
		return (ROUT);
	if (c == '|')
		return (PIP);
	if (c == '\'')
		return (SQ);
	if (c == '\"')
		return (DQ);
	if (c == '&')
		return (AND);
	return (-1);
}
