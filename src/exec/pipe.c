/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:14:00 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/06 13:48:08 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		g_shell->is_inside_pipe = 1;
		run_exec(pcmd->left, env);
	}
	waitpid(g_shell->pid, NULL, 0);
	if (fork_child() == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		g_shell->is_inside_pipe = 1;
		run_exec(pcmd->right, env);
	}
	waitpid(g_shell->pid, NULL, 0);
	close(fd[1]);
	close(fd[0]);
}
