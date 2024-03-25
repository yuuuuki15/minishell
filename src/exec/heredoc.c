/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 09:29:33 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/25 09:34:26 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Handles the SIGINT signal during heredoc input.
 * @param sig int: The signal number.
 */
static void	ft_sig_here(int sig)
{
	if (sig == SIGINT)
	{
		unlink(".file1.tmp");
		g_sig = 130;
	}
}

// opens temp file for heredoc
static int	ft_open_file(void)
{
	int	fd;

	fd = open(".file1.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putendl_fd("minishell: error occured while opening file",
			STDERR_FILENO);
		exit(1);
	}
	return (fd);
}

// cleans heredoc fds, temp file, and shell
static void	clean_heredoc(int fd, t_redircmd *rcmd, t_shell *shell)
{
	close(fd);
	close(rcmd->fd);
	unlink(".file1.tmp");
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
	int		fd;

	fd = ft_open_file();
	signal(SIGINT, &ft_sig_here);
	while (1)
	{
		line = readline("heredoc> ");
		if (g_sig == 130)
		{
			close(fd);
			clean_exit(shell);
			exit(130);
		}
		if (line == NULL || ft_strcmp(line, rcmd->file) == 0)
			break ;
		line = process_line(line, shell);
		ft_putendl_fd(line, fd);
		if (line)
			free(line);
	}
	clean_heredoc(fd, rcmd, shell);
}

/**
 * Manages heredoc redirection by creating a temporary file.
 * @param rcmd t_redircmd*: The redirection command.
 * @param shell t_shell*: The shell instance.
 */
void	ft_here_doc(t_redircmd *rcmd, t_shell *shell)
{
	int	status;

	rcmd->fd = open(".file1.tmp", O_RDONLY | O_CREAT | O_TRUNC, 0644);
	if (shell->in_fd != STDIN_FILENO && shell->in_fd != -1)
		close(shell->in_fd);
	shell->in_fd = rcmd->fd;
	if (shell->in_fd < 0)
		return ;
	signal(SIGQUIT, SIG_IGN);
	if (fork_child(shell) == 0)
		ft_here(rcmd, shell);
	waitpid(shell->pid, &status, 0);
	ft_signal_manager(2);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		shell->exit_status = 130;
	else
		shell->exit_status = WEXITSTATUS(status);
}
