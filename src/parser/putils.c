/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:23:09 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/01 17:54:40 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_line(char *line)
{
	ft_printf("%s\n", line);
}

int	handle_space(void)
{
	ft_printf("%s\n", "no command entered");
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_issym(char c)
{
	if (c == '<')
		return (LT);
	if (c == '>')
		return (RINPUT);
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

// deletes a sub string from a string specifying start and len
char	*ft_delstr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s) - start)
		return (NULL);
	sub = (char *) malloc ((ft_strlen(s) - len + 1) * sizeof(char));
	if (sub == 0)
		return (NULL);
	i = 0;
	while (i < start)
	{
		sub[i] = s[i];
		i++;
	}
	while (s[i + start + len] != '\0')
	{
		sub[i] = s[i + start + len];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
