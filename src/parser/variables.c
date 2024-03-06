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

// extracts var name from string 
void	get_var_name(t_tok *tok, int i, int size, char *str)
{
	i++;
	tok->len = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
	{
		tok->len++;
		i++;
	}
	while (str[i] != '\0' && ft_isspace(str[i]) == 0 && str[i] != '$')
	{
		tok->len++;
		i++;
	}
	tok->str = ft_strtrim(ft_substr(str, tok->s_loc + size, tok->len), " ");
	tok->size = tok->len + size - 1;
	tok->cut = i;
}

// extracts the name of the variable and stores in tok
void	get_var(t_tok *tok, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' &&  str[i] != '$')
		i++;
	tok->s_loc = i;
	get_var_name(tok, i, 1, str);
	ft_printf("variable name extracted is: .%s.\n", tok->str);
}

// locate $var
void	expand_var(char **tab)
{
	int		i;
	t_tok	tok;
	char	*expansion;

	i = 0;
	while (tab[i] != NULL)
	{
		if (find_var(tab[i]) != 0)
		{
			ft_printf("there are $ in arg: .%s.\n", tab[i]);
			get_var(&tok, tab[i]);
			expansion = ft_strdup(ft_get_env(tok.str)->value);
			ft_printf("this expands to: %s\n", expansion);
			ft_printf("len: %d, loc: %d cut: %d\n", tok.len, tok.s_loc, tok.cut);
			ft_printf("length of str %d\n", (int)ft_strlen(tab[i]));
		}
		i++;
	}
	free(expansion);
}
