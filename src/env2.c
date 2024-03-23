/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:40:31 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/23 17:59:14 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if a string is a valid identifier.
 * @param str char*: The string to check.
 * @return int: 1 if valid, 0 otherwise.
 * Error: Returns 0 if str is NULL, empty, starts with a digit, or contains
 * characters other than alphabets and underscores.
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
 * Displays all environment variables.
 * @param shell t_shell*: The shell containing the environment variables.
 * No return value.
*/
void	ft_show_env(t_shell *shell)
{
	t_env	*curr;

	if (shell->env == NULL)
		return ;
	curr = shell->env;
	while (curr != NULL)
	{
		if (curr->exported)
		{
			ft_printf("%s=", curr->key);
			ft_printf("%s\n", curr->value);
		}
		curr = curr->next;
	}
}

/**
 * Cleans all environment variables.
 * @param shell t_shell*: The shell containing the environment variables.
 * No return value.
*/
void	ft_clean_env(t_shell *shell)
{
	t_env	*curr;
	t_env	*to_delete;

	curr = shell->env;
	while (curr != NULL)
	{
		if (curr->key)
			free(curr->key);
		if (curr->value)
			free(curr->value);
		to_delete = curr;
		curr = curr->next;
		if (to_delete)
			free(to_delete);
	}
	shell->env = NULL;
}

/**
 * Sets the PWD environment variable if it does not exist.
 * @param shell t_shell*: The shell to modify.
 * @return int: 0 on success, 1 on failure.
 * Error: Returns 1 if getting the current working directory fails or adding
 * the PWD variable fails.
*/
int	ft_set_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*key;
	char	*value;

	if (ft_get_env("PWD", shell) == NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			ft_clean_env(shell);
			return (1);
		}
		key = ft_get_key("PWD");
		value = ft_strdup(cwd);
		if (ft_add_env(key, value, shell) == 1)
		{
			ft_clean_env(shell);
			return (1);
		}
	}
	return (0);
}

// I think underscore is the full path of the first argumentof the command.
// for example, if you execute ./minishell, underscore will be full path of minishell
// and if you run env -i ./minishell, you will have full path of minishell
int	ft_set_underscore(t_shell *shell)
{
	char	*key;
	char	*value;

	ft_printf("_ -> %s\n", getenv("_"));
	if (ft_get_env("_", shell) == NULL)
	{
		if (getenv("_") != NULL)
		{
			key = ft_strdup("_");
			value = ft_strdup(getenv("_"));
			if (ft_add_env(key, value, shell) == 1)
			{
				ft_clean_env(shell);
				return (1);
			}
		}
	}
	return (0);
}
