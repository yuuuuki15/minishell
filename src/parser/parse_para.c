/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_para.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:46:42 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/11 17:15:42 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sets values to 2 if para, 1 if inside ()
void	set_para_values(int *in_para, char *str, int *in_quotes)
{
	int	openp;
	int	i;
	int	val;

	i = 0;
	val = 2;
	openp = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(' && in_quotes[i] == 0)
		{
			in_para[i] = val++;
			openp = 1;
		}
		else if (str[i] == ')' && in_quotes[i] == 0)
		{
			in_para[i] = --val;
			openp = 0;
		}
		else if (openp == 1)
			in_para[i] = 1;
		i++;
	}
}

// makes an integer array that denotes if in quotes and quote type
int	*parse_para(char *str)
{
	int	*in_para;
	int	len;
	int	*in_quotes;

	in_quotes = parse_quotes(str);
	len = ft_strlen(str);
	in_para = (int *) malloc (len * sizeof(int));
	if (in_para == 0)
		return (NULL);
	zero_array(in_para, len);
	set_para_values(in_para, str, in_quotes);
	free (in_quotes);
	return (in_para);
}

// check if there are parentheses
int	has_para(char *str)
{
	int	*in_para;
	int	i;
	int	ret;

	in_para = parse_para(str);
	i = 0;
	ret = 0;
	while (str[i] != '\0')
	{
		if (in_para[i] != 0)
			ret = 1;
		i++;
	}
	free (in_para);
	return (ret);
}
