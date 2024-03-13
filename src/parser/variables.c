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

int	ft_isallowed(char c)
{
	if (ft_isalnum(c) == 1)
		return (1);
	if (c == '/')
		return (0);
	if (c == '_')
		return (1);
	return (0);
}

// extracts var name from string noting location and length
void	get_var_name(t_tok *tok, int i, int size, char *str)
{
	char	*sub;

	i++;
	tok->len = 0;
	if (str[i] == '?')
	{
		tok->len++;
		i++;
	}
	else
	{
		while (str[i] != '\0' && ft_isallowed(str[i]) == 1)
		{
			tok->len++;
			i++;
		}
	}
	sub = ft_substr(str, tok->s_loc + size, tok->len);
	tok->str = ft_strtrim(sub, " ");
	tok->size = tok->len + size - 1;
	tok->cut = i;
	free (sub);
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
char	*expand_var(char *str, t_shell *shell)
{
	t_tok	tok;
	char	*expansion;
	char	*frank;

	if (find_var(str) != 0)
	{
		ft_printf("%d\n", find_var(str));
		get_var(&tok, str);
		ft_printf("%s\n", tok.str);
		if (ft_strcmp(tok.str, "?") == 0)
			expansion = ft_itoa(shell->exit_status);
		else
		{
			if (ft_get_env(tok.str, shell) == NULL)
				return (NULL);
			else
				expansion = ft_strdup(ft_get_env(tok.str, shell)->value);
		}
		frank = frankenstein(str, &tok, expansion);
		free(expansion);
		if (find_var(frank))
			frank = expand_var(frank, shell);
		return (frank);
	}
	if (tok.str)
		free (tok.str);
	return (str);
}
