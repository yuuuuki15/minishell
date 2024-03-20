/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:27:07 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/10 17:43:04 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// removes variable then pastes in expansion
char	*frankenstein(char *str, t_tok *tok, char *exp)
{
	char	*frank;
	char	*s1;
	char	*s2;
	int		len;

	s1 = ft_strdup(str);
	s1[tok->s_loc] = '\0';
	s2 = ft_strjoin(s1, exp);
	free (s1);
	len = (int)ft_strlen(str) - tok->cut;
	s1 = ft_substr(str, tok->cut, len);
	frank = ft_strjoin(s2, s1);
	free (s1);
	free (s2);
	return (frank);
}

// expand variable
char	*get_expansion(t_tok *tok, t_shell *shell)
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

// locate $var then expand it, recursively if necessary
char	*expand_var(char *str, t_shell *shell)
{
	t_tok	tok;
	char	*expansion;
	char	*frank;
	char	*subfrank;

	if (find_var(str) != 0)
	{
		get_var(&tok, str);
		expansion = get_expansion(&tok, shell);
		frank = frankenstein(str, &tok, expansion);
		free(expansion);
		if (tok.str)
			free (tok.str);
		if (find_var(frank) != 0)
		{
			subfrank = ft_strdup(frank);
			free (frank);
			frank = expand_var(subfrank, shell);
			free (subfrank);
		}
		return (frank);
	}
	return (ft_strdup(str));
}
