/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:39:26 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/19 14:39:47 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free an environment node
void	free_node(t_env *ptr)
{
	if (ptr)
	{
		if (ptr->key)
			free(ptr->key);
		if (ptr->value)
			free(ptr->value);
		free(ptr);
	}
}

/**
 * @param char* key
 *
 * This function takes a key and finds the matching
 * environment variable and unset it
*/
void	ft_unset_env(char *key, t_shell *shell)
{
	t_env	*curr;
	t_env	*to_delete;

	curr = shell->env;
	to_delete = NULL;
	if (curr == NULL)
		return ;
	if (ft_strcmp(curr->key, key) == 0)
	{
		shell->env = curr->next;
		free_node(curr);
		return ;
	}
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			to_delete = curr->next;
			curr->next = curr->next->next;
			free_node(to_delete);
			return ;
		}
		curr = curr->next;
	}
}
