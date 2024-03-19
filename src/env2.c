/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:40:31 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/19 13:45:11 by ykawakit         ###   ########.fr       */
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
 * This function displays all environment variables
*/
void	ft_show_env(t_shell *shell)
{
	t_env	*curr;

	if (shell->env == NULL)
		return ;
	curr = shell->env;
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
		free(curr->key);
		free(curr->value);
		free(curr);
		return ;
	}
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			to_delete = curr->next;
			curr->next = curr->next->next;
			free(to_delete->key);
			free(to_delete->value);
			free(to_delete);
			return ;
		}
		curr = curr->next;
	}
}

/**
 * clean all environment variable with free method.
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
 * @param t_shel *shell
 * Function to set the environment variable named PWD when it does not exist
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
		value = ft_get_value(cwd);
		if (ft_add_env(key, value, shell) == 1)
		{
			ft_clean_env(shell);
			return (1);
		}
	}
	return (0);
}
