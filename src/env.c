/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:38:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/09 14:50:50 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param char* str
 * @return int result
 *
 * This function checks if the given string is a valid identifier.
 * The first character must not be a digit, and it must consist only
 * of alphabets or underscores.
*/
int	ft_is_valid_identifier(char *str)
{
	if (str == NULL || *str == '\0' || ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

/**
 * @param char **env
 *
 * This function takes an array of environment variables and initializes them
 * to the variable t_env inside global variable shell.
*/
int	ft_init_env(char **env, t_shell *g_shell)
{
	int		i;
	char	cwd[PATH_MAX];
	char	*key;
	char	*value;

	if (env == NULL)
		return (1);
	i = -1;
	while (env[++i])
	{
		key = ft_get_key(env[i]);
		value = ft_get_value(env[i]);
		if (ft_add_env(key, value, g_shell) == 1)
		{
			ft_clean_env(g_shell);
			return (1);
		}
	}
	if (ft_get_env("PWD", g_shell) == NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			ft_clean_env(g_shell);
			return (1);
		}
		key = ft_get_key("PWD");
		value = ft_get_value(cwd);
		if (ft_add_env(key, value, g_shell) == 1)
		{
			ft_clean_env(g_shell);
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
t_env	*ft_get_env(char *name, t_shell *g_shell)
{
	t_env	*curr;

	curr = g_shell->env;
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
void	ft_update_env(char *key, char *value, t_shell *g_shell)
{
	t_env	*curr;

	curr = g_shell->env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			break ;
		curr = curr->next;
	}
	free(curr->value);
	curr->value = value;
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
int	ft_add_env(char *key, char *value, t_shell *g_shell)
{
	t_env	*new;
	t_env	*curr;

	if (key == NULL || ft_is_valid_identifier(key) == 0)
		return (1);
	if (ft_get_env(key, g_shell) != NULL)
	{
		ft_update_env(key, value, g_shell);
		return (0);
	}
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	curr = g_shell->env;
	if (curr == NULL)
	{
		g_shell->env = new;
		return (0);
	}
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	return (0);
}
