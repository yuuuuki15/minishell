/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:41:30 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/10 17:43:04 by ykawakit         ###   ########.fr       */
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

	pathname = ft_get_path(cmd->argv[0], shell);
	res = execve(pathname, cmd->argv, env);
	if (res < 0)
	{
		if (pathname != NULL)
			free(pathname);
		ft_putstr_fd(ERR_COMMAND_NOT_FOUND, STDERR_FILENO);
		ft_putendl_fd(cmd->argv[0], STDERR_FILENO);
		ft_free_tab(cmd->argv);
		free (cmd);
		exit(127);
	}
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
	shell->pid = fork_child(shell);
	if (shell->pid == 0)
	{
		dup_descriptors(shell);
		ft_exec(ecmd, env, shell);
	}
	else
	{
		waitpid(shell->pid, &status, 0);
		shell->exit_status = WEXITSTATUS(status);
		reset_descriptors(shell);
	}
}

// directs the execution of the cammand tree
void	run_exec(t_cmd *cmd, char **env, t_shell *shell)
{
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
			waitpid(shell->pid, NULL, 0);
	}
	if (cmd->type == IFTHEN || cmd->type == IFOR)
		manage_andor(cmd, env, shell);
}
