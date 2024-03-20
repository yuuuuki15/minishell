/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:07:26 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:48:20 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Extracts the file name from a string for redirection.
 * @param tok t_tok*: The token to update with file name information.
 * @param i int: The current index in the string.
 * @param size int: The size of the redirection token.
 * @param str char*: The string to extract the file name from.
 */
static void	get_file_name(t_tok *tok, int i, int size, char *str)
{
	char	*sub;
	int		*q_check;

	q_check = parse_quotes(str);
	i++;
	tok->len = 0;
	while (str[i] != '\0' && ft_isspace(str[i]) && q_check[i] == 0)
	{
		tok->len++;
		i++;
	}
	while (str[i] != '\0'
		&& ((ft_isspace(str[i]) == 0 && ft_istok(str[i]) == -1)
			|| q_check[i] != 0))
	{
		tok->len++;
		i++;
	}
	sub = ft_substr(str, tok->s_loc + size, tok->len);
	tok->str = ft_strtrim(sub, " ");
	tok->size = tok->len + size - 1;
	tok->cut = i;
	free (sub);
	free (q_check);
}

/**
 * Handles redirection errors by checking for multiple redirect tokens.
 * @param tok t_tok*: The token to update with error or file name information.
 * @param i int: The current index in the string.
 * @param size int: The size of the redirection token.
 * @param str char*: The string to check for redirection errors.
 */
static void	redir_err(t_tok *tok, int i, int size, char *str)
{
	if (ft_istok(str[i + 1]) == -1)
		get_file_name(tok, i, size, str);
	else
	{
		ft_printf("syntax error near unexpected token \'%c\'\n", str[i + 1]);
		tok->tok = FERR;
	}
}

/**
 * Identifies and processes redirection tokens in a string.
 * @param tok t_tok*: The token to update with redirection information.
 * @param i int: The current index in the string.
 * @param str char*: The string to parse for redirection tokens.
 */
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
	redir_err(tok, i, size, str);
}
