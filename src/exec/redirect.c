/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:17:07 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/04 09:17:27 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_redir(t_cmd *cmd, char **env)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	if (rcmd->mode == RIN)
	{
		rcmd->fd = open(rcmd->file, O_RDONLY);
		g_shell->in_fd = rcmd->fd;
	}
	else if (rcmd->mode == ROUT)
	{
		rcmd->fd = open(rcmd->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		g_shell->out_fd = rcmd->fd;
	}
	else if (rcmd->mode == ROUTA)
	{
		rcmd->fd = open(rcmd->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		g_shell->out_fd = rcmd->fd;
	}
	if (rcmd->fd < 0)
	{
		ft_printf("open file error, clean this up!\n");
		exit(1);
	}
	run_exec(rcmd->cmd, env);
}
