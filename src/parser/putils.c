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

// checks if char is a symbol maybe don't need this
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
	if (c == '$')
		return (DOL);
	if (c == '\\')
		return (BS);
	return (-1);
}

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
