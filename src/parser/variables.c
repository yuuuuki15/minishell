/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:27:07 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/09 14:57:04 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return number of $ in str that are not in sigle quotes
int	find_var(char *str)
{
	int	i;
	int	nd;
	int	*in_quotes;

	in_quotes = parse_quotes(str);
	i = 0;
	nd = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && in_quotes[i] != 1)
			nd++;
		i++;
	}
	free (in_quotes);
	return (nd);
}

// extracts var name from string noting location and length
void	get_var_name(t_tok *tok, int i, int size, char *str)
{
	i++;
	tok->len = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
	{
		tok->len++;
		i++;
	}
	while (str[i] != '\0' && ft_isspace(str[i]) == 0
		&& ft_issym(str[i]) == -1 && str[i] != '$')
	{
		tok->len++;
		i++;
	}
	tok->str = ft_strtrim(ft_substr(str, tok->s_loc + size, tok->len), " ");
	tok->size = tok->len + size - 1;
	tok->cut = i;
}

// extracts the name of the variable and stores it in tok
void	get_var(t_tok *tok, char *str)
{
	int	i;
	int	*in_quotes;

	in_quotes = parse_quotes(str);
	i = 0;
	while (str[i] != '\0' && (str[i] != '$' || in_quotes[i] == 1))
		i++;
	tok->s_loc = i;
	get_var_name(tok, i, 1, str);
	free (in_quotes);
}

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

// locate $var then expand it, recursively if necessary
char	*expand_var(char *str, t_shell *g_shell)
{
	t_tok	tok;
	char	*expansion;
	char	*frank;

	if (find_var(str) != 0)
	{
		get_var(&tok, str);
		if (ft_strcmp(tok.str, "?") == 0)
			expansion = ft_itoa(g_shell->exit_status);
		else
		{
			if (ft_get_env(tok.str, g_shell) == NULL)
				return (str);
			else
				expansion = ft_strdup(ft_get_env(tok.str, g_shell)->value);
		}
		frank = frankenstein(str, &tok, expansion);
		free(expansion);
		if (find_var(frank))
			frank = expand_var(frank, g_shell);
		return (frank);
	}
	return (str);
}
