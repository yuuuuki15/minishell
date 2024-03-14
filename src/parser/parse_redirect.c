/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:07:26 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/13 17:50:57 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extracts file name from string
void	get_file_name(t_tok *tok, int i, int size, char *str)
{
	char	*sub;

	i++;
	tok->len = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
	{
		tok->len++;
		i++;
	}
	while (str[i] != '\0' && ft_isspace(str[i]) == 0 && ft_issym(str[i]) == -1)
	{
		tok->len++;
		i++;
	}
	sub = ft_substr(str, tok->s_loc + size, tok->len);
	tok->str = ft_strtrim(sub, " ");
	tok->size = tok->len + size - 1;
	tok->cut = i;
	free (sub);
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
	if (ft_istok(str[i + 1]) == -1)
		get_file_name(tok, i, size, str);
	else
	{
		ft_printf("syntax error near unexpected token \'%c\'\n", str[i + 1]);
		tok->tok = FERR;
	}
}
