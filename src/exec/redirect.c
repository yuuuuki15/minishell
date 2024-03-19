/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:17:07 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/18 15:15:39 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sig_here(int sig)
{
	if (sig == SIGINT)
	{
		exit(130);
	}
}

static void	ft_here(t_redircmd *rcmd, t_shell *shell)
{
	char	*line;
	int		fd;

	fd = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putendl_fd("minishell: error occured while opening file",
			STDERR_FILENO);
		exit(1);
	}
	while (1)
	{
		signal(SIGINT, &ft_sig_here);
		line = readline("heredoc> ");
		if (ft_strcmp(line, rcmd->file) == 0)
			break ;
		ft_putendl_fd(line, fd);
		if (line)
			free(line);
	}
	close(fd);
	close(rcmd->fd);
	clean_exit(shell);
	exit(0);
}

static void	ft_here_doc(t_redircmd *rcmd, t_shell *shell)
{
	int	pid;
	int	status;

	if (shell->in_fd < 0)
		return ;
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		ft_here(rcmd, shell);
	waitpid(pid, &status, 0);
	ft_signal_manager(2);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		shell->exit_status = 130;
	else
		shell->exit_status = WEXITSTATUS(status);
}

static void	ft_redir_helper(t_redircmd *rcmd, t_shell *shell)
{
	if (rcmd->mode == RIN && rcmd->file != NULL)
	{
		rcmd->fd = open(rcmd->file, O_RDONLY);
		shell->in_fd = rcmd->fd;
	}
	else if (rcmd->mode == ROUT && rcmd->file != NULL)
	{
		rcmd->fd = open(rcmd->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		shell->out_fd = rcmd->fd;
	}
	else if (rcmd->mode == ROUTA && rcmd->file != NULL)
	{
		rcmd->fd = open(rcmd->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		shell->out_fd = rcmd->fd;
	}
	else if (rcmd->mode == RHERE)
	{
		rcmd->fd = open("/tmp/file1", O_RDONLY | O_CREAT | O_TRUNC, 0644);
		shell->in_fd = rcmd->fd;
		ft_here_doc(rcmd, shell);
	}
}

void	manage_redir(t_cmd *cmd, char **env, t_shell *shell)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	ft_redir_helper(rcmd, shell);
	if (shell->exit_status != 0)
		return ;
	if (rcmd->fd < 0)
	{
		shell->exit_status = 1;
		ft_printf("open file error\n");
	}
	else
	{
		if (check_tree(rcmd->cmd, shell) == 0)
			run_exec(rcmd->cmd, env, shell);
	}
}
