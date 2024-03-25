/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:17:07 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/23 17:06:44 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Assists in managing different types of redirections.
 * @param rcmd t_redircmd*: The redirection command.
 * @param shell t_shell*: The shell instance.
 */
static void	ft_redir_helper(t_redircmd *rcmd, t_shell *shell)
{
	if (rcmd->mode == RIN && rcmd->file != NULL)
	{
		rcmd->fd = open(rcmd->file, O_RDONLY);
		if (shell->in_fd != STDIN_FILENO && shell->in_fd != -1)
			close(shell->in_fd);
		shell->in_fd = rcmd->fd;
	}
	else if (rcmd->mode == ROUT && rcmd->file != NULL)
	{
		rcmd->fd = open(rcmd->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (shell->out_fd != STDOUT_FILENO && shell->out_fd != -1)
			close(shell->out_fd);
		shell->out_fd = rcmd->fd;
	}
	else if (rcmd->mode == ROUTA && rcmd->file != NULL)
	{
		rcmd->fd = open(rcmd->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (shell->out_fd != STDOUT_FILENO && shell->out_fd != -1)
			close(shell->out_fd);
		shell->out_fd = rcmd->fd;
	}
	else if (rcmd->mode == RHERE)
		ft_here_doc(rcmd, shell);
}

/**
 * Manages redirection for a given command.
 * @param cmd t_cmd*: The command to manage redirection for.
 * @param env char**: The environment variables.
 * @param shell t_shell*: The shell instance.
 */
void	manage_redir(t_cmd *cmd, char **env, t_shell *shell)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	if (check_file(rcmd->file, shell) == 1)
		return ;
	ft_redir_helper(rcmd, shell);
	if (rcmd->fd < 0)
	{
		shell->exit_status = 1;
		ft_putendl_fd("open file error", STDERR_FILENO);
	}
	else
	{
		if (rcmd->cmd != NULL)
			run_exec(rcmd->cmd, env, shell);
		else
			reset_descriptors(shell);
	}
}
