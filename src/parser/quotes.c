/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:18:48 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/10 17:43:04 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// removes quotes from arguments after expanding variables not in single quotes
char	**clean_quotes(char **tab, t_shell *shell)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		tab[i] = expand_var(tab[i], shell);
		tab[i] = remove_quotes(tab[i]);
		i++;
	}
	return (tab);
}

// trims paired quotes from string
char	*remove_quotes(char *str)
{
	int	*in_quotes;
	int	i;
	int	j;

	if (str == NULL)
		return (NULL);
	in_quotes = parse_quotes(str);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (in_quotes[i] == 3)
			i++;
		else
		{
			str[j] = str[i];
			j++;
			i++;
		}
	}
	str[j] = '\0';
	free (in_quotes);
	return (str);
}

// checks if quotes are all balanced, if not will return 0
int	balance_quotes(char *str)
{
	int	sq_tok;
	int	dq_tok;
	int	i;

	i = 0;
	sq_tok = 0;
	dq_tok = 0;
	while (str[i] != '\0')
	{
		if (ft_issym(str[i]) == SQ && dq_tok % 2 == 0)
			sq_tok++;
		if (ft_issym(str[i]) == DQ && sq_tok % 2 == 0)
			dq_tok++;
		i++;
	}
	if (sq_tok % 2 == 0 && dq_tok % 2 == 0)
		return (1);
	return (0);
}

// sets values to 3 if quote, 2 in inside "", 1 if inside ''
void	set_quote_values(int *in_quotes, char *str)
{
	int	i;
	int	sq_tok;
	int	dq_tok;

	i = -1;
	sq_tok = 0;
	dq_tok = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'' && dq_tok % 2 == 0)
		{
			in_quotes[i] = 3;
			sq_tok++;
		}
		else if (str[i] == '\"' && sq_tok % 2 == 0)
		{
			in_quotes[i] = 3;
			dq_tok++;
		}
		else if (dq_tok % 2 != 0)
			in_quotes[i] = 2;
		else if (sq_tok % 2 != 0)
			in_quotes[i] = 1;
	}
}

// makes an integer array that denotes if in quotes and quote type
int	*parse_quotes(char *str)
{
	int	*in_quotes;

	in_quotes = (int *) malloc ((ft_strlen(str) + 1) * sizeof(int));
	if (in_quotes == 0)
		return (NULL);
	ft_memset(in_quotes, 0, sizeof(in_quotes));
	set_quote_values(in_quotes, str);
	return (in_quotes);
}
