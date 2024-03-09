/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:14:00 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/09 17:53:24 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	p_child(t_listcmd *pcmd, char **env, int fd[2], t_shell *g_shell)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	g_shell->is_inside_pipe = 1;
	g_shell->out_fd = fd[1];
	run_exec(pcmd->left, env, g_shell);
}

static void	p_parent(t_listcmd *pcmd, char **env, int fd[2], t_shell *g_shell)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	g_shell->is_inside_pipe = 1;
	g_shell->in_fd = fd[0];
	run_exec(pcmd->right, env, g_shell);
}

void	manage_pipe(t_cmd *cmd, char **env, t_shell *g_shell)
{
	t_listcmd	*pcmd;
	int			fd[2];

	pcmd = (t_listcmd *)cmd;
	if (pipe(fd) < 0)
		exit(1);
	if (fork_child(g_shell) == 0)
	{
		p_child(pcmd, env, fd, g_shell);
		exit(0);
	}
	else
	{
		waitpid(g_shell->pid, NULL, 0);
		p_parent(pcmd, env, fd, g_shell);
		exit(0);
	}
}
