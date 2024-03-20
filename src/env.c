/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:38:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/20 22:56:47 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initializes environment variables from an array to the global shell variable.
 * @param env char**: Array of environment variables.
 * @param shell t_shell*: Pointer to the shell structure.
 * @return int: 0 on success, 1 on error.
 * @error If env is NULL or adding an environment variable fails, returns 1.
*/
int	ft_init_env(char **env, t_shell *shell)
{
	int		i;
	char	*key;
	char	*value;

	if (env == NULL)
		return (ft_set_pwd(shell));
	i = -1;
	while (env[++i])
	{
		key = ft_get_key(env[i]);
		value = ft_get_value(env[i]);
		if (ft_add_env(key, value, shell) == 1)
		{
			ft_clean_env(shell);
			return (1);
		}
	}
	return (0);
}

/**
 * Retrieves an environment variable by its key.
 * @param name char*: The key of the environment variable to find.
 * @param shell t_shell*: Pointer to the shell structure.
 * @return t_env*: Pointer to the environment variable, or NULL if not found.
*/
t_env	*ft_get_env(char *name, t_shell *shell)
{
	t_env	*curr;

	curr = shell->env;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->key, name) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/**
 * Updates the value of an existing environment variable.
 * @param key char*: The key of the environment variable to update.
 * @param value char*: The new value for the environment variable.
 * @param shell t_shell*: Pointer to the shell structure.
 * @return int: 0 on success.
*/
static int	ft_update_env(char *key, char *value, t_shell *shell)
{
	t_env	*curr;

	curr = shell->env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			break ;
		curr = curr->next;
	}
	free(curr->value);
	curr->value = value;
	return (0);
}

/**
 * Creates a new environment variable and adds it to the environment list.
 * @param key char*: The key of the new environment variable.
 * @param value char*: The value of the new environment variable.
 * @param shell t_shell*: Pointer to the shell structure.
 * @return int: 0 on success, 1 on error.
 * @error If memory allocation for the new environment variable fails, returns 1.
*/
static int	ft_create_env(char *key, char *value, t_shell *shell)
{
	t_env	*new;
	t_env	*curr;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	curr = shell->env;
	if (curr == NULL)
	{
		shell->env = new;
		return (0);
	}
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	return (0);
}

/**
 * Adds or updates an environment variable in the shell's environment.
 * @param key char*: The key of the environment variable.
 * @param value char*: The value of the environment variable.
 * @param shell t_shell*: Pointer to the shell structure.
 * @return int: 0 on success, 1 on error.
 * @error If the key is invalid or memory allocation fails, returns 1.
*/
int	ft_add_env(char *key, char *value, t_shell *shell)
{
	if (ft_is_valid_identifier(key) == 0)
		return (1);
	if (ft_get_env(key, shell) != NULL)
		return (ft_update_env(key, value, shell));
	return (ft_create_env(key, value, shell));
}
