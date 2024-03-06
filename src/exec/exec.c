/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:41:30 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/04 09:16:10 by mevonuk          ###   ########.fr       */
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

// after child is done, reset file descriptors
void	reset_descriptors(void)
{
	if (g_shell->in_fd > 0)
		close(g_shell->in_fd);
	if (g_shell->out_fd > 1)
		close(g_shell->out_fd);
	g_shell->in_fd = 0;
	g_shell->out_fd = 1;
}

// duplicate descriptors in child
void	dup_descriptors(void)
{
	if (g_shell->in_fd > 0)
	{
		dup2(g_shell->in_fd, 0);
		close(g_shell->in_fd);
	}
	if (g_shell->out_fd > 1)
	{
		dup2(g_shell->out_fd, 1);
		close(g_shell->out_fd);
	}
}

// directs the execution of the cammand tree
// BACK is managed and resubmited to run_exec prior to fork
// REDIR is good for a single file, pipe, I don't know
void	run_exec(t_cmd *cmd, char **env)
{
	t_execcmd	*ecmd;

	if (cmd->type == REDIR)
		manage_redir(cmd, env);
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ft_is_builtin(ecmd))
		{
			g_shell->exit_status = ft_builtin_manager((t_execcmd *)cmd);
			return ;
		}
		g_shell->pid = fork_child();
		if (g_shell->pid == 0)
		{
			dup_descriptors();
			ft_exec(ecmd, env);
		}
		else
			wait(NULL);
		reset_descriptors();
	}
	if (cmd->type == BACK)
		manage_back(cmd, env);
	if (cmd->type == PIPE)
		manage_pipe(cmd, env);
}
