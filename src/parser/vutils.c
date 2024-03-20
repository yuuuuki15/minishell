/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:17:03 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 11:13:58 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return number of $ in str that are not in sigle quotes
int	find_var(char *str)
{
	int	i;
	int	nd;
	int	*in_quotes;

	in_quotes = parse_quotes(str);
	i = 0;
	nd = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && in_quotes[i] != 1 && str[i + 1] != '\0'
			&& str[i + 1] != ' ' && str[i + 1] != '\"')
			nd++;
		i++;
	}
	free (in_quotes);
	return (nd);
}

// extracts var name from string noting location and length
static void	get_var_name(t_tok *tok, int i, int size, char *str)
{
	char	*sub;

	i++;
	tok->len = 0;
	if (str[i] == '?')
	{
		tok->len++;
		i++;
	}
	else
	{
		while (str[i] != '\0' && ft_isallowed(str[i]) == 1)
		{
			tok->len++;
			i++;
		}
	}
	sub = ft_substr(str, tok->s_loc + size, tok->len);
	tok->str = ft_strtrim(sub, " ");
	tok->size = tok->len + size - 1;
	tok->cut = i;
	free (sub);
}

// extracts the name of the variable and stores it in tok
void	get_var(t_tok *tok, char *str)
{
	int	i;
	int	*in_quotes;

	in_quotes = parse_quotes(str);
	i = 0;
	while (str[i] != '\0' && (str[i] != '$' || in_quotes[i] == 1))
		i++;
	tok->s_loc = i;
	get_var_name(tok, i, 1, str);
	free (in_quotes);
}
