/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:18:48 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/11 17:50:35 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// removes quotes from arguments after expanding variables not in single quotes
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
