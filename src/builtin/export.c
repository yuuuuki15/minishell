/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:34:13 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/06 17:40:54 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints an error message for invalid identifiers.
 * @param arg The argument that was found to be an invalid identifier.
 */
static void	print_invalid_identifier(char *arg)
{
	ft_putstr_fd("export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

/**
 * Handles the case where the argument does not contain an equal sign.
 * If the argument is a valid identifier and does not exist in the environment,
 * it is added with an empty value.
 * @param arg The argument to be processed.
 * @return Returns 0 on success, 1 on failure.
 */
static int	handle_no_equal(char *arg)
{
	if (ft_is_valid_identifier(arg))
	{
		if (ft_get_env(arg) != NULL)
			return (0);
		ft_add_env(ft_strdup(arg), ft_strdup(""));
		return (0);
	}
	print_invalid_identifier(arg);
	return (1);
}

/**
 * Handles the case where the argument contains an equal sign.
 * Splits the argument into a key and value and
 * adds/updates the environment variable.
 * @param arg The argument to be processed.
 * @param equal_pos The position of the equal sign in the argument.
 * @return Returns 0 on success, 1 on failure.
 */
static int	handle_with_equal(char *arg, int equal_pos)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, equal_pos);
	value = ft_strdup(arg + equal_pos + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (1);
	}
	ft_add_env(key, value);
	return (0);
}

/**
 * Adds or updates an environment variable based on the provided argument.
 * If the argument does not contain an equal sign, it processes it accordingly.
 * If it does, it splits the argument into a key
 * and value for the environment variable.
 * @param arg The argument to be processed.
 * @return Returns 0 on success, 1 on failure.
 */
static int	ft_add_or_update_env(char *arg)
{
	int	equal_pos;

	equal_pos = ft_strchr(arg, '=') - arg;
	if (equal_pos < 0)
		return (handle_no_equal(arg));
	else
		return (handle_with_equal(arg, equal_pos));
}

/**
 * Handles the export command execution.
 * Displays the current environment variables if no arguments are provided.
 * Attempts to add or update environment variables based on the provided
 * arguments.
 * @param cmd The command structure
 * @return exit status
 */
int	export(t_execcmd *cmd)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (cmd->argv[1] == NULL)
	{
		ft_show_env();
		return (0);
	}
	while (cmd->argv[++i])
		if (ft_add_or_update_env(cmd->argv[i]) != 0)
			status = 1;
	return (status);
}
