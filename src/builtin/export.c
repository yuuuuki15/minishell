/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:24 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/02 17:50:28 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @param char* arg
 * @return int status
 *
 * This function adds or updates an environment variable based on the argument provided.
 * If the argument does not contain an equal sign, it checks if the argument is a valid
 * identifier. If it is, and the environment variable already exists, it does nothing.
 * Otherwise, it adds the variable with an empty value. If the argument is not a valid
 * identifier, it prints an error message. If the argument contains an equal sign, it
 * splits the argument into a key and a value. If either the key or value cannot be
 * obtained, it returns 1. Otherwise, it adds or updates the environment variable with
 * the key and value. It returns 0 on success and 1 on failure.
 */
static int	ft_add_or_update_env(char *arg)
{
	char	*key;
	char	*value;
	int		equal_pos;

	equal_pos = ft_strchr(arg, '=') - arg;
	if (equal_pos < 0)
	{
		if (ft_is_valid_identifier(arg))
		{
			if (ft_get_env(arg) != NULL)
				return (0);
			ft_add_env(ft_strdup(arg), strdup(""));
			return (0);
		}
		ft_putstr_fd("export: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	if ((key = ft_get_key(arg)) == NULL)
		return (1);
	if ((value = ft_get_value(arg)) == NULL)
	{
		free(key);
		return (1);
	}
	ft_add_env(key, value);
	return (0);
}

/**
 * @param t_execcmd* cmd
 * @return int status
 *
 * This function handles the export command execution. It takes a command
 * structure as an argument, which contains the arguments passed to the export
 * command. If no arguments are provided, it displays the current environment
 * variables. For each argument provided, it attempts to add or update the
 * environment variable. It returns 0 if all variables are successfully added
 * or updated, and 1 if any variable fails to be added or updated due to invalid
 * identifiers.
 */
int	export(t_execcmd *cmd)
{
	int	i;
	int	status;

	if (cmd->argv[1] == NULL)
	{
		ft_show_env();
		return (0);
	}
	i = 0;
	status = 0;
	while (cmd->argv[++i])
	{
		if (ft_add_or_update_env(cmd->argv[i]) != 0)
			status = 1;
	}
	return (status);
}
