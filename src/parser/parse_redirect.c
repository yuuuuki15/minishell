/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:07:26 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/12 14:07:39 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extracts file name from string
void	get_file_name(t_tok *tok, int i, int size, char *str)
{
	i++;
	tok->len = 0;
	if (str[i] == '<' || str[i] == '>')
		ft_printf("syntax error near unexpected token \'%c\'\n", str[i]);
	while (str[i] != '\0' && ft_isspace(str[i]))
	{
		tok->len++;
		i++;
	}
	while (str[i] != '\0' && ft_isspace(str[i]) == 0)
	{
		tok->len++;
		i++;
	}
	tok->str = ft_strtrim(ft_substr(str, tok->s_loc + size, tok->len), " ");
	tok->size = tok->len + size - 1;
	tok->cut = i;
}

// get information for redirection tokens
void	get_redir_token(t_tok *tok, int i, char *str)
{
	int	size;

	size = 1;
	if (ft_istok(str[i]) == RIN && ft_istok(str[i + 1]) == RIN)
	{
		i++;
		tok->tok = RHERE;
		size++;
	}
	else if (ft_istok(str[i]) == RIN && ft_istok(str[i + 1]) != RIN)
		tok->tok = RIN;
	else if (ft_istok(str[i]) == ROUT && ft_istok(str[i + 1]) != ROUT)
		tok->tok = ROUT;
	else if (ft_istok(str[i]) == ROUT && ft_istok(str[i + 1]) == ROUT)
	{
		tok->tok = ROUTA;
		i++;
		size++;
	}
	get_file_name(tok, i, size, str);
}
