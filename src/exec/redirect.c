/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:17:07 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/13 18:33:17 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_here_doc(t_redircmd *rcmd, t_shell *shell)
{
	int		pipefd[2];
	char	*line;

	pipe(pipefd);
	while (1)
	{
		ft_signal_manager(2);
		ft_printf("heredoc> ");
		line = ft_get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, rcmd->file, ft_strlen(line) - 1) == 0)
			break ;
		ft_putendl_fd(line, pipefd[1]);
		if (line)
			free(line);
	}
	close(pipefd[1]);
	shell->in_fd = pipefd[0];
}

static void	ft_redir_helper(t_redircmd *rcmd, t_shell *shell)
{
	if (rcmd->file != NULL && (rcmd->file[0] == '<' || rcmd->file[0] == '>'))
	{
		shell->exit_status = 2;
		rcmd->fd = -1;
		return ;
	}
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
		rcmd->fd = STDIN_FILENO;
		ft_here_doc(rcmd, shell);
	}
}

void	manage_redir(t_cmd *cmd, char **env, t_shell *shell)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	ft_redir_helper(rcmd, shell);
	if (rcmd->fd < 0)
	{
		if (rcmd->file[0] != '<' && rcmd->file[0] != '>')
			ft_printf("open file error\n");
	}
	else
		run_exec(rcmd->cmd, env, shell);
}
