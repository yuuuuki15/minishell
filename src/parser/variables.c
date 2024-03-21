/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:27:07 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:53:24 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Combines strings around a variable expansion.
 * @param str char*: The original string.
 * @param tok t_tok*: Token containing variable location and length.
 * @param exp char*: The expansion of the variable.
 * @return char*: The new string with the variable expanded.
 */
static char	*frankenstein(char *str, t_tok *tok, char *exp, t_shell *shell)
{
	char	*frank;
	char	*s1;
	char	*s2;
	int		len;

	s1 = ft_strdup(str);
	s1[tok->s_loc] = '\0';
	s1 = remove_quotes(s1);
	s2 = ft_strjoin(s1, exp);
	free (s1);
	len = (int)ft_strlen(str) - tok->cut;
	s1 = ft_substr(str, tok->cut, len);
	if (find_var(s1) != 0)
	{
		frank = ft_strdup(s1);
		free (s1);
		s1 = expand_var(frank, shell);
		free (frank);
	}
	else
		s1 = remove_quotes(s1);
	frank = ft_strjoin(s2, s1);
	free (s1);
	free (s2);
	return (frank);
}

/**
 * Retrieves the expansion for a given variable.
 * @param tok t_tok*: Token containing the variable name.
 * @param shell t_shell*: Shell environment for variable lookup.
 * @return char*: The expansion of the variable or a space if not found.
 */
static char	*get_expansion(t_tok *tok, t_shell *shell)
{
	char	*expansion;

	if (ft_strcmp(tok->str, "?") == 0)
		expansion = ft_itoa(shell->exit_status);
	else
	{
		if (ft_get_env(tok->str, shell) == NULL)
			expansion = ft_strdup(" ");
		else
			expansion = ft_strdup(ft_get_env(tok->str, shell)->value);
	}
	return (expansion);
}

/**
 * Expands variables in a string recursively.
 * @param str char*: The string to expand variables in.
 * @param shell t_shell*: Shell environment for variable lookup.
 * @return char*: The string with all variables expanded.
 */
char	*expand_var(char *str, t_shell *shell)
{
	t_tok	tok;
	char	*expansion;
	char	*frank;

	if (find_var(str) != 0)
	{
		get_var(&tok, str);
		expansion = get_expansion(&tok, shell);
		frank = frankenstein(str, &tok, expansion, shell);
		free(expansion);
		if (tok.str)
			free (tok.str);
		return (frank);
	}
	else
		str = remove_quotes(str);
	return (ft_strdup(str));
}
