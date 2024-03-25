/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:36:26 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/25 20:48:17 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if the command is a built-in command.
 * @param cmd t_execcmd*: The command structure to be executed.
 * @return int: 1 if the command is a built-in command, 0 otherwise.
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
 * Manages the execution of built-in commands.
 * @param cmd t_execcmd*: The command structure to be executed.
 * @param shell t_shell*: The shell instance.
 * @return int: The result of the built-in command execution.
 * Error cases: Returns specific error codes based on the command execution
 * failure.
 */
int	ft_builtin_manager(t_execcmd *cmd, t_shell *shell)
{
	int	result;
	int	fd;

	fd = STDOUT_FILENO;
	if (shell->out_fd != STDOUT_FILENO)
		fd = shell->out_fd;
	result = 0;
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		result = ft_echo(cmd, fd);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		result = ft_cd(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		result = ft_export(cmd, shell, fd);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		result = ft_unset(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		result = ft_env(cmd, shell, fd);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		result = ft_pwd(cmd, shell, fd);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		result = ft_exit(cmd, shell);
	return (result);
}
