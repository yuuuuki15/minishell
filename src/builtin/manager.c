/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:36:26 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/13 19:06:57 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param cmd The command structure to be executed.
 * @return 1 if the command is a built-in command, 0 otherwise.
 *
 * Checks if the command is a built-in command.
 */
int	ft_is_builtin(t_execcmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0
		|| ft_strcmp(cmd->argv[0], "cd") == 0
		|| ft_strcmp(cmd->argv[0], "export") == 0
		|| ft_strcmp(cmd->argv[0], "unset") == 0
		|| ft_strcmp(cmd->argv[0], "env") == 0
		|| ft_strcmp(cmd->argv[0], "pwd") == 0
		|| ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	else
		return (0);
}

/**
 * @param cmd The command structure to be executed.
 * @return The result of the built-in command execution.
 *
 * Manages the execution of built-in commands.
 */
int	ft_builtin_manager(t_execcmd *cmd, t_shell *shell)
{
	int	result;

	result = 0;
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		result = ft_echo(cmd);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		result = ft_cd(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		result = ft_export(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		result = ft_unset(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		result = ft_env(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		result = ft_pwd(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		result = ft_exit(cmd, shell);
	return (result);
}
