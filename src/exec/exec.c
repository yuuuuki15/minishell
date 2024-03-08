/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:41:30 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/08 17:20:07 by ykawakit         ###   ########.fr       */
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
void	ft_exec(t_execcmd *cmd, char **env)
{
	char	*pathname;
	int		res;

	pathname = ft_get_path(cmd->argv[0]);
	res = execve(pathname, cmd->argv, env);
	if (res < 0)
	{
		if (pathname != NULL)
			free(pathname);
		ft_putstr_fd(ERR_COMMAND_NOT_FOUND, STDERR_FILENO);
		ft_putendl_fd(cmd->argv[0], STDERR_FILENO);
		ft_free_tab(cmd->argv);
		free (cmd);
		exit(errno);
	}
}

static void	handle_builtin(t_execcmd *ecmd)
{
	dup_descriptors();
	g_shell->exit_status = ft_builtin_manager(ecmd);
	reset_descriptors();
}
// manage the executable part of the tree by forking
void	manage_exec(t_cmd *cmd, char **env)
{
	t_execcmd	*ecmd;

	ecmd = (t_execcmd *)cmd;
	if (ft_is_builtin(ecmd))
	{
		handle_builtin(ecmd);
		return ;
	}
	g_shell->pid = fork_child();
	if (g_shell->pid == 0)
	{
		// if (!g_shell->is_inside_pipe)
			dup_descriptors();
		ft_exec(ecmd, env);
	}
	else
	{
		waitpid(g_shell->pid, NULL, 0);
		reset_descriptors();
	}
}

// directs the execution of the cammand tree
void	run_exec(t_cmd *cmd, char **env)
{
	if (cmd->type == REDIR)
		manage_redir(cmd, env);
	if (cmd->type == EXEC)
		manage_exec(cmd, env);
	if (cmd->type == BACK)
		manage_back(cmd, env);
	if (cmd->type == PIPE)
	{
		if (fork_child() == 0)
			manage_pipe(cmd, env);
		else
			waitpid(g_shell->pid, NULL, 0);
	}
}
