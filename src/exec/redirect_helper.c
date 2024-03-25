/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 08:41:24 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/25 08:41:40 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_only_var(t_tok *tok, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && (str[i] != '$'))
		i++;
	tok->s_loc = i;
	get_var_name(tok, i, 1, str);
}

// finds variables regardless of quotes
static int	find_only_var(char *str)
{
	int	i;
	int	nd;

	i = 0;
	nd = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0'
			&& str[i + 1] != ' ' && str[i + 1] != '\"')
			nd++;
		i++;
	}
	return (nd);
}

/**
 * Combines strings around a variable expansion.
 * @param str char*: The original string.
 * @param tok t_tok*: Token containing variable location and length.
 * @param exp char*: The expansion of the variable.
 * @return char*: The new string with the variable expanded.
 */
static char	*frankenstein_nq(char *str, t_tok *tok, char *exp)
{
	char	*frank;
	char	*s1;
	char	*s2;

	s1 = ft_strdup(str);
	s1[tok->s_loc] = '\0';
	s2 = ft_strjoin(s1, exp);
	free (s1);
	s1 = ft_substr(str, tok->cut, (int)ft_strlen(str) - tok->cut);
	frank = ft_strjoin(s2, s1);
	free (s1);
	free (s2);
	return (frank);
}

static char	*expand_only_var(char *str, t_shell *shell)
{
	t_tok	tok;
	char	*expansion;
	char	*frank;
	char	*temp;

	if (find_only_var(str) != 0)
	{
		get_only_var(&tok, str);
		expansion = get_expansion(&tok, shell);
		frank = frankenstein_nq(str, &tok, expansion);
		free(expansion);
		if (find_only_var(frank) != 0)
		{
			temp = expand_only_var(frank, shell);
			free (frank);
			frank = temp;
		}
		if (tok.str)
			free (tok.str);
		return (frank);
	}
	return (ft_strdup(str));
}

char	*process_line(char *str, t_shell *shell)
{
	char	*temp;

	temp = expand_only_var(str, shell);
	ft_printf("expanded: %s\n", temp);
	free (str);
	str = temp;
	return (str);
}
