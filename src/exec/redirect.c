/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:17:07 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/09 17:49:52 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_here_doc(t_redircmd *rcmd, t_shell *g_shell)
{
	int		pipefd[2];
	char	*line;

	pipe(pipefd);
	ft_printf("%s\n", rcmd->file);
	while (1)
	{
		ft_printf("heredoc> ");
		line = ft_get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, rcmd->file, ft_strlen(rcmd->file)) == 0)
			break ;
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	g_shell->in_fd = pipefd[0];
}

static void	ft_redir_helper(t_redircmd *rcmd, t_shell *g_shell)
{
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
	else if (rcmd->mode == RHERE)
	{
		rcmd->fd = STDIN_FILENO;
		ft_here_doc(rcmd, g_shell);
	}
}

void	manage_redir(t_cmd *cmd, char **env, t_shell *g_shell)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	ft_redir_helper(rcmd, g_shell);
	if (rcmd->fd < 0)
	{
		ft_printf("open file error, clean this up!\n");
		exit(1);
	}
	run_exec(rcmd->cmd, env, g_shell);
}
