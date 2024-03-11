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
char	**clean_quotes(char **tab, t_shell *shell)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (ft_strcmp(tab[i], "<<<") == 0)
			tab[i] = NULL;
		else if (ft_strncmp(tab[i], "<<<", 3) == 0
			&& (tab[i][3] == '<' || tab[i][3] == '>'))
		{
			ft_printf("syntax error near unexpected token \'%c\'\n", tab[i][3]);
			tab[0] = NULL;
		}
		else
		{
			if (i == 0 && tab[i][0] == '(')
				tab[i] = ft_strtrim(tab[i], "()");
			else if (i > 0 && tab[i][0] == '(')
			{
				ft_printf("syntax error near unexpected token \'%s\'\n",
					ft_strtrim(tab[i], "()"));
				tab[0] = NULL;
			}
			tab[i] = expand_var(tab[i], shell);
			tab[i] = remove_quotes(tab[i]);
		}
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

// set array to zero
void	zero_array(int *in_quotes, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		in_quotes[i] = 0;
		i++;
	}
}

// makes an integer array that denotes if in quotes and quote type
int	*parse_quotes(char *str)
{
	int	*in_quotes;
	int	len;

	len = ft_strlen(str);
	in_quotes = (int *) malloc (len * sizeof(int));
	if (in_quotes == 0)
		return (NULL);
	zero_array(in_quotes, len);
	set_quote_values(in_quotes, str);
	return (in_quotes);
}
