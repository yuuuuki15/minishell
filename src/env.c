/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:38:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/13 13:32:26 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param char **env
 *
 * This function takes an array of environment variables and initializes them
 * to the variable t_env inside global variable shell.
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
 * @param char* name
 * @return t_env env
 *
 * Take a key string and return environment pointer.
 * return NULL if there's no environment.
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
 * @param char* key
 * @param char* value
 *
 * This function will take key and value and update the environment
 * with the sam key name env.
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
 * @param char* key
 * @param char* value
 * @return int
 *
 * take key and value, then register to environment.
 * return 0 on success. return 1 on error.
 * Attention: parameters, key and value should be dynamically allocated string.
*/
int	ft_add_env(char *key, char *value, t_shell *shell)
{
	if (ft_is_valid_identifier(key) == 0)
		return (1);
	if (ft_get_env(key, shell) != NULL)
		return (ft_update_env(key, value, shell));
	return (ft_create_env(key, value, shell));
}
