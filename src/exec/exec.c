/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:41:30 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/25 20:50:31 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Executes a command using the provided path and environment.
 * @param cmd t_execcmd*: The command to execute.
 * @param env char**: Environment variables.
 * @param shell t_shell*: Shell instance for error handling.
 * Error: Prints error message and exits with 127 if command execution fails.
*/
static void	ft_exec(t_execcmd *cmd, char **env, t_shell *shell)
{
	char	*pathname;
	char	**env_array;
	int		res;

	(void)env;
	res = 0;
	pathname = ft_get_path(cmd->argv[0], shell);
	env_array = NULL;
	if (pathname != NULL)
	{
		env_array = env_to_char_array(shell);
		res = execve(pathname, cmd->argv, env_array);
	}
	if (res < 0 || pathname != NULL)
		free(pathname);
	ft_free_tab(env_array);
	ft_putstr_fd(ERR_COMMAND_NOT_FOUND, STDERR_FILENO);
	if (cmd->argv != NULL && cmd->argv[0] != NULL)
		ft_putendl_fd(cmd->argv[0], STDERR_FILENO);
	clean_exit(shell);
	exit(127);
}

/**
 * Handles execution of built-in commands.
 * @param ecmd t_execcmd*: The command to execute.
 * @param shell t_shell*: Shell instance for error handling.
*/
static void	handle_builtin(t_execcmd *ecmd, t_shell *shell)
{
	shell->exit_status = ft_builtin_manager(ecmd, shell);
}

/**
 * Manages execution by forking for non-built-in commands.
 * @param cmd t_cmd*: The command to manage.
 * @param env char**: Environment variables.
 * @param shell t_shell*: Shell instance for error handling.
*/
static void	manage_exec(t_cmd *cmd, char **env, t_shell *shell)
{
	t_execcmd	*ecmd;
	int			status;

	ecmd = (t_execcmd *)cmd;
	if (ft_is_builtin(ecmd))
	{
		handle_builtin(ecmd, shell);
		return ;
	}
	shell->pid = fork_child(shell);
	if (shell->pid == 0)
	{
		dup_descriptors(shell);
		ft_exec(ecmd, env, shell);
	}
	else
	{
		waitpid(shell->pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			shell->exit_status = 130;
		else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			shell->exit_status = 131;
		else
			shell->exit_status = WEXITSTATUS(status);
	}
}

/**
 * Directs the execution based on the type of command.
 * @param cmd t_cmd*: The command to execute.
 * @param env char**: Environment variables.
 * @param shell t_shell*: Shell instance for error handling.
*/
void	run_exec(t_cmd *cmd, char **env, t_shell *shell)
{
	ft_signal_manager(2);
	if (cmd->type == REDIR)
		manage_redir(cmd, env, shell);
	else if (cmd->type == EXEC)
	{
		if (check_tree(cmd, shell) == 0)
			manage_exec(cmd, env, shell);
	}
	else if (cmd->type == BACK)
		manage_back(cmd, env, shell);
	else if (cmd->type == PIPE)
	{
		if (fork_child(shell) == 0)
			manage_pipe(cmd, env, shell);
		else
		{
			waitpid(shell->pid, &(shell->exit_status), 0);
			shell->exit_status = WEXITSTATUS(shell->exit_status);
		}
	}
	else if (cmd->type == IFTHEN || cmd->type == IFOR)
		manage_andor(cmd, env, shell);
}
