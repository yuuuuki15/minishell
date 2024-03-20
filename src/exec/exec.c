/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:41:30 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/20 09:27:03 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param t_execcmd *cmd
 *
 * This function takes executive command provided by parser,
 * checks path using env info from shell then
 * executes command. Print error message when error occurs.
*/
void	ft_exec(t_execcmd *cmd, char **env, t_shell *shell)
{
	char	*pathname;
	int		res;

	res = 0;
	pathname = ft_get_path(cmd->argv[0], shell);
	if (pathname != NULL)
		res = execve(pathname, cmd->argv, env);
	if (res < 0 || pathname != NULL)
		free(pathname);
	ft_putstr_fd(ERR_COMMAND_NOT_FOUND, STDERR_FILENO);
	// if (cmd->argv != NULL && cmd->argv[0] != NULL)
	// 	ft_putendl_fd(cmd->argv[0], STDERR_FILENO);
	clean_exit(shell);
	exit(127);
}

static void	handle_builtin(t_execcmd *ecmd, t_shell *shell)
{
	dup_descriptors(shell);
	shell->exit_status = ft_builtin_manager(ecmd, shell);
	reset_descriptors(shell);
}

// manage the executable part of the tree by forking
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
	dup_descriptors(shell);
	shell->pid = fork_child(shell);
	if (shell->pid == 0)
		ft_exec(ecmd, env, shell);
	else
	{
		waitpid(shell->pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			shell->exit_status = 130;
		else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			shell->exit_status = 131;
		else
			shell->exit_status = WEXITSTATUS(status);
		reset_descriptors(shell);
	}
}

// directs the execution of the command tree
void	run_exec(t_cmd *cmd, char **env, t_shell *shell)
{
	ft_signal_manager(2);
	if (cmd->type == REDIR)
		manage_redir(cmd, env, shell);
	if (cmd->type == EXEC)
		manage_exec(cmd, env, shell);
	if (cmd->type == BACK)
		manage_back(cmd, env, shell);
	if (cmd->type == PIPE)
	{
		if (fork_child(shell) == 0)
			manage_pipe(cmd, env, shell);
		else
		{
			waitpid(shell->pid, &(shell->exit_status), 0);
			shell->exit_status = WEXITSTATUS(shell->exit_status);
		}
	}
	if (cmd->type == IFTHEN || cmd->type == IFOR)
		manage_andor(cmd, env, shell);
}
