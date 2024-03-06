/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:27:07 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/06 17:27:35 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return number of $ in str
int	find_var(char *str)
{
	int	i;
	int	nd;

	i = 0;
	nd = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			nd++;
		i++;
	}
	return (nd);
}

// extracts the name of the variable and stores in tok
void	get_var(t_tok *tok, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' &&  str[i] != '$')
		i++;
	tok->s_loc = i;
	get_file_name(tok, i, 1, str);
	ft_printf("variable name extracted is: .%s.\n", tok->str);
}

// locate $var
void	expand_var(char **tab)
{
	int		i;
	t_tok	tok;

	i = 0;
	while (tab[i] != NULL)
	{
		if (find_var(tab[i]) != 0)
		{
			ft_printf("there are $ in arg: .%s.\n", tab[i]);
			get_var(&tok, tab[i]);
			ft_printf("this expands to: %s\n", ft_get_env(tok.str)->value);
		}
		i++;
	}
}
