/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:14:00 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/07 17:54:51 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_pipe_side(t_pipecmd *pcmd, char **env, int fd[2], int side)
{
	if (side == 0)
	{
		close(fd[0]);
		g_shell->is_inside_pipe = 1;
		g_shell->out_fd = fd[1];
		run_exec(pcmd->left, env);
	}
	else
	{
		close(fd[1]);
		g_shell->is_inside_pipe = 1;
		g_shell->in_fd = fd[0];
		run_exec(pcmd->right, env);
	}
}

void	manage_pipe(t_cmd *cmd, char **env)
{
	t_pipecmd	*pcmd;
	int			fd[2];

	pcmd = (t_pipecmd *)cmd;
	if (pipe(fd) < 0)
	{
		ft_printf("Pipe error\n");
		exit(1);
	}
	if (fork_child() == 0)
	{
		execute_pipe_side(pcmd, env, fd, 0);
		exit(1);
	}
	else
	{
		waitpid(g_shell->pid, NULL, 0);
		if (fork_child() == 0)
		{
			execute_pipe_side(pcmd, env, fd, 1);
			exit(1);
		}
		waitpid(g_shell->pid, NULL, 0);
		close(fd[0]);
		close(fd[1]);
	}
}
