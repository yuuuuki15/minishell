/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:39:26 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:57:39 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Frees an environment node.
 * @param ptr t_env*: Pointer to the environment node to be freed.
 */
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
 * Unsets an environment variable.
 * @param key char*: The key of the environment variable to unset.
 * @param shell t_shell*: The shell containing the environment variables.
 * Removes the environment variable matching the given key from the shell's
 * environment list and frees the associated memory.
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
