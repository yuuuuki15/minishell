/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:34:13 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/20 22:29:26 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints an error message for invalid identifiers.
 * @param arg char*: The argument that was found to be an invalid identifier.
 */
static void	print_invalid_identifier(char *arg)
{
	ft_putstr_fd(ERR_EXPORT_NOT_VALID_IDENTIFIER, STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
}

/**
 * Handles the case where the argument contains an equal sign. Splits the
 * argument into a key and value and adds/updates the environment variable.
 * @param arg char*: The argument to be processed.
 * @param equal_pos int: The position of the equal sign in the argument.
 * @param shell t_shell*: The shell instance.
 * @return int: Returns 0 on success, 1 on failure.
 * Error cases: Returns 1 if the key is an invalid identifier or memory
 * allocation fails.
 */
static int	handle_with_equal(char *arg, int equal_pos, t_shell *shell)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, equal_pos);
	if (ft_is_valid_identifier(key) == 0)
	{
		print_invalid_identifier(key);
		free(key);
		return (1);
	}
	value = ft_strdup(arg + equal_pos + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (1);
	}
	return (ft_add_env(key, value, shell));
}

/**
 * Adds or updates an environment variable based on the provided argument.
 * If the argument does not contain an equal sign, it processes it accordingly.
 * If it does, it splits the argument into a key and value for the environment
 * variable.
 * @param arg char*: The argument to be processed.
 * @param shell t_shell*: The shell instance.
 * @return int: Returns 0 on success, 1 on failure.
 * Error cases: Returns 1 if the argument contains an equal sign but fails to
 * process correctly.
 */
static int	ft_add_or_update_env(char *arg, t_shell *shell)
{
	int	equal_pos;

	equal_pos = ft_strchr(arg, '=') - arg;
	if (equal_pos < 0)
		return (0);
	else
		return (handle_with_equal(arg, equal_pos, shell));
}

/**
 * Handles the export command execution. Displays the current environment
 * variables if no arguments are provided. Attempts to add or update environment
 * variables based on the provided arguments.
 * @param cmd t_execcmd*: The command structure.
 * @param shell t_shell*: The shell instance.
 * @return int: Exit status. Returns 0 if all arguments are processed
 * successfully, 1 if any argument fails to be added or updated.
 * Error cases: Returns 1 if any argument fails to be added or updated.
 */
int	ft_export(t_execcmd *cmd, t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (cmd->argv[1] == NULL)
	{
		ft_show_env(shell);
		return (0);
	}
	while (cmd->argv[++i])
		if (ft_add_or_update_env(cmd->argv[i], shell) != 0)
			status = 1;
	return (status);
}
