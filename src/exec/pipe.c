/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:14:00 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:39:22 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Cleans up resources before exiting due to pipe failure.
 * @param shell The current shell instance.
 */
static void	ft_pipe_cleaner(t_shell *shell)
{
	clean_exit(shell);
	exit(1);
}

/**
 * Executes the child process part of a pipe.
 * @param pcmd The command to execute.
 * @param env The environment variables.
 * @param fd File descriptors for the pipe.
 * @param shell The current shell instance.
 */
static void	p_child(t_listcmd *pcmd, char **env, int fd[2], t_shell *shell)
{
	close(fd[0]);
	shell->is_inside_pipe = 1;
	shell->out_fd = fd[1];
	if (check_tree(pcmd->left, shell) == 0)
		run_exec(pcmd->left, env, shell);
}

/**
 * Executes the parent process part of a pipe.
 * @param pcmd The command to execute.
 * @param env The environment variables.
 * @param fd File descriptors for the pipe.
 * @param shell The current shell instance.
 */
static void	p_parent(t_listcmd *pcmd, char **env, int fd[2], t_shell *shell)
{
	close(fd[1]);
	if (shell->in_fd != STDIN_FILENO)
		close(shell->in_fd);
	shell->is_inside_pipe = 1;
	shell->in_fd = fd[0];
	if (check_tree(pcmd->right, shell) == 0)
		run_exec(pcmd->right, env, shell);
}

/**
 * Manages the creation and execution of a pipe.
 * @param cmd The command structure containing the pipe.
 * @param env The environment variables.
 * @param shell The current shell instance.
 */
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
