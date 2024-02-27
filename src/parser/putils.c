/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:23:09 by mevonuk           #+#    #+#             */
/*   Updated: 2024/02/27 15:49:47 by ykawakit         ###   ########.fr       */
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
		return (GT);
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
	if (c == '(')
		return (OP);
	if (c == ')')
		return (CP);
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
