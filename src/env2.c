/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:40:31 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/06 17:16:07 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This function displays all environment variables
*/
void	ft_show_env(void)
{
	t_env	*curr;

	if (g_shell->env == NULL)
		return ;
	curr = g_shell->env;
	while (curr != NULL)
	{
		ft_printf("%s=", curr->key);
		ft_printf("%s\n", curr->value);
		curr = curr->next;
	}
}

/**
 * @param char* key
 *
 * This function takes a key and finds the matching
 * environment variable and unset it
*/
void	ft_unset_env(char *key)
{
	t_env	*curr;
	t_env	*to_delete;

	curr = g_shell->env;
	if (curr == NULL)
		return ;
	if (ft_strcmp(curr->key, key) == 0)
	{
		g_shell->env = curr->next;
		free(curr);
		return ;
	}
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			to_delete = curr->next;
			curr->next = curr->next->next;
			free(to_delete);
			return ;
		}
		curr = curr->next;
	}
}

/**
 * clean all environment variable with free method.
*/
void	ft_clean_env(void)
{
	t_env	*curr;
	t_env	*to_delete;

	curr = g_shell->env;
	while (curr != NULL)
	{
		to_delete = curr;
		curr = curr->next;
		free(to_delete);
	}
	g_shell->env = NULL;
}
