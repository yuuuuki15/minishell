/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:38:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/27 18:26:16 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param char* name
 * @return t_env env
 *
 * Take a key string and return environment pointer.
 * return NULL if there's no environment.
*/
t_env	*ft_get_env(char *name)
{
	int	i;
	t_env	*curr;

	curr = shell.env;
	while (curr)
	{
		if (ft_strcmp(curr->key, name) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/**
 * @param char* key
 * @param char* value
 * @return int
 *
 * This function will take key and value and update the environment
 * with the sam key name env.
*/
void	ft_update_env(char *key, char *value)
{
	t_env	*curr;

	curr = shell.env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			break ;
		curr = curr->next;
	}
	free(curr->value);
	curr->value = ft_strdup(value);
}

/**
 * @param char* key
 * @param char* value
 * @return int
 *
 * take key and value, then register to environment.
 * return 0 on success. return 1 on error.
*/
int	ft_add_env(char *key, char *value)
{
	t_env	*new;
	t_env	*curr;

	if (ft_get_env(key) == NULL)
	{
		ft_update_env(key, value);
		return (0);
	}
	new = malloc(sieof(t_env));
	if (new == NULL)
		return (1);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	curr = shell.env;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	return (0);
}
