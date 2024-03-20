/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:18:48 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:52:47 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Removes quotes from arguments after expanding variables not in single quotes.
 * @param tab char**: Array of strings to clean quotes from.
 * @param shell t_shell*: Shell structure for variable expansion context.
 */
void	clean_quotes(char **tab, t_shell *shell)
{
	int		i;
	char	*exp;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		if (i > 0 && tab[i][0] == '(')
		{
			ft_printf("syntax error near unexpected token \'(\'\n");
			free (tab[i]);
			tab[0] = ft_strdup(" ");
		}
		i++;
	}
	i = 0;
	while (tab[i] != NULL)
	{
		exp = expand_var(tab[i], shell);
		free (tab[i]);
		tab[i] = exp;
		tab[i] = remove_quotes(tab[i]);
		i++;
	}
}

/**
 * Trims paired quotes from a string.
 * @param str char*: The string to remove quotes from.
 * @return char*: The modified string without paired quotes.
 */
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

/**
 * Sets values to indicate quote types within a string.
 * @param in_quotes int*: Array to store quote type indicators.
 * @param str char*: The string to analyze for quotes.
 */
static void	set_quote_values(int *in_quotes, char *str)
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

/**
 * Creates an integer array indicating quote types within a string.
 * @param str char*: The string to analyze for quotes.
 * @return int*: Array indicating quote types, NULL on error.
 * @error Returns NULL if str is NULL or memory allocation fails.
 */
int	*parse_quotes(char *str)
{
	int	*in_quotes;
	int	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	in_quotes = (int *) malloc (len * sizeof(int));
	if (in_quotes == 0)
		return (NULL);
	zero_array(in_quotes, len);
	set_quote_values(in_quotes, str);
	return (in_quotes);
}
