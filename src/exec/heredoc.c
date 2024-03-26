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
		write(2, "\n", 1);
		close(g_fd);
		unlink(".heredoc_tmp");
		g_sig = 130;
	}
}

/**
 * Executes the heredoc redirection.
 * @param rcmd t_redircmd*: The redirection command.
 * @param shell t_shell*: The shell instance.
 */
static void	ft_here(t_redircmd *rcmd, t_shell *shell)
{
	char	*line;

	while (1 && g_sig != 130)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_sig_here);
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, rcmd->file) == 0)
			break ;
		line = process_line(line, shell);
		ft_putendl_fd(line, g_fd);
		if (line)
			free(line);
	}
}

/**
 * Manages heredoc redirection by creating a temporary file.
 * @param rcmd t_redircmd*: The redirection command.
 * @param shell t_shell*: The shell instance.
 */
void	ft_here_doc(t_redircmd *rcmd, t_shell *shell)
{
	rcmd->fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (rcmd->fd < 0)
	{
		ft_putendl_fd("ERR_HEREDOC", 2);
		exit(1);
	}
	ft_here(rcmd, shell);
	close(rcmd->fd);
	g_fd = open(".heredoc_tmp", O_RDONLY);
	shell->in_fd = g_fd;
}
