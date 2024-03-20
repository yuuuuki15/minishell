/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:14:00 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 12:15:23 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipe_cleaner(t_shell *shell)
{
	clean_exit(shell);
	exit(1);
}

static void	p_child(t_listcmd *pcmd, char **env, int fd[2], t_shell *shell)
{
	close(fd[0]);
	shell->is_inside_pipe = 1;
	shell->out_fd = fd[1];
	run_exec(pcmd->left, env, shell);
}

static void	p_parent(t_listcmd *pcmd, char **env, int fd[2], t_shell *shell)
{
	close(fd[1]);
	if (shell->in_fd != STDIN_FILENO)
		close(shell->in_fd);
	shell->is_inside_pipe = 1;
	shell->in_fd = fd[0];
	run_exec(pcmd->right, env, shell);
}

void	manage_pipe(t_cmd *cmd, char **env, t_shell *shell)
{
	t_listcmd	*pcmd;
	int			fd[2];

	pcmd = (t_listcmd *)cmd;
	if (pipe(fd) < 0)
		ft_pipe_cleaner(shell);
	if (fork_child(shell) == 0)
	{
		p_child(pcmd, env, fd, shell);
		close(fd[1]);
		clean_exit(shell);
		exit(shell->exit_status);
	}
	else
	{
		waitpid(shell->pid, NULL, 0);
		p_parent(pcmd, env, fd, shell);
		close(fd[0]);
		clean_exit(shell);
		exit(shell->exit_status);
	}
}
