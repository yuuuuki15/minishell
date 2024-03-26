/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 09:29:33 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/25 22:45:09 by ykawakit         ###   ########.fr       */
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
		g_sig = 130;
		exit(130);
	}
}

static void	ft_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
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

	g_fd = shell->fd[1];
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_sig_here);
		line = readline("heredoc> ");
		if (g_sig == 130)
		{
			clean_exit(shell);
			//exit(130);
		}
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

	signal(SIGQUIT, &ft_sig_child);
	signal(SIGINT, &ft_sig_child);
	if (pipe(shell->fd) == -1)
		ft_error(ERR_PIPE);
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
