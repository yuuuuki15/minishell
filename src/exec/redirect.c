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

void	manage_redir2(t_cmd *cmd)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	close(rcmd->fd);
	rcmd->fd = open(rcmd->file, rcmd->mode);
	ft_printf("fd: %d\n", rcmd->fd);
	if (rcmd->fd < 0)
	{
		ft_printf("open file error, clean this up!\n");
		exit(1);
	}
	if (rcmd->mode == O_RDONLY)
		dup2(rcmd->fd, 0);
	free(rcmd->file);
}

// currently manages a redirect to an input file
// need to add redirect to outfile, heredoc, outfile append
void	manage_redir(t_cmd *cmd, char **env)
{
	t_redircmd	*rcmd;
	t_execcmd	*ecmd;

	rcmd = (t_redircmd *)cmd;
	g_shell->pid = fork_child();
	if (g_shell->pid == 0)
	{
		close(rcmd->fd);
		rcmd->fd = open(rcmd->file, rcmd->mode);
		ft_printf("fd: %d\n", rcmd->fd);
		if (rcmd->fd < 0)
		{
			ft_printf("open file error, clean this up!\n");
			exit(1);
		}
		if (rcmd->mode == O_RDONLY)
			dup2(rcmd->fd, 0);
		free(rcmd->file);
		ecmd = (t_execcmd *)rcmd->cmd;
		ft_exec(ecmd, env);
	}	
	else
		wait(NULL);
}
