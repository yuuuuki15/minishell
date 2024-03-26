/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 09:29:33 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/26 13:50:26 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_fd;

/**
 * Handles the SIGINT signal during heredoc input.
 * @param sig int: The signal number.
 */
static void	ft_sig_here(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		close(g_fd);
		exit(130);
	}
}

// cleans heredoc fds, temp file, and shell
static void	clean_heredoc(t_shell *shell)
{
	close(shell->fd[1]);
	clean_exit(shell);
	exit(0);
}

/**
 * Executes the heredoc redirection.
 * @param rcmd t_redircmd*: The redirection command.
 * @param shell t_shell*: The shell instance.
 */
static void	ft_here(t_redircmd *rcmd, t_shell *shell)
{
	char	*line;

	signal(SIGINT, &ft_sig_here);
	g_fd = shell->fd[1];
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strcmp(line, rcmd->file) == 0)
			break ;
		line = process_line(line, shell);
		ft_putendl_fd(line, shell->fd[1]);
		if (line)
			free(line);
	}
	clean_heredoc(shell);
}

/**
 * Manages heredoc redirection by creating a temporary file.
 * @param rcmd t_redircmd*: The redirection command.
 * @param shell t_shell*: The shell instance.
 */
void	ft_here_doc(t_redircmd *rcmd, t_shell *shell)
{
	int	status;

	if (pipe(shell->fd) == -1)
		ft_error(ERR_PIPE);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (fork_child(shell) == 0)
	{
		close(shell->fd[0]);
		ft_here(rcmd, shell);
	}
	else
	{
		rcmd->fd = shell->fd[0];
		close(shell->fd[1]);
		shell->in_fd = shell->fd[0];
		waitpid(shell->pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			shell->exit_status = 130;
		else
			shell->exit_status = WEXITSTATUS(status);
	}
}
