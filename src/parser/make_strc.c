/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_strc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:23:56 by mevonuk           #+#    #+#             */
/*   Updated: 2024/02/27 11:24:12 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*make_execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*make_backcmd(t_cmd *subcmd)
{
	t_backcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = BACK;
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}

t_cmd   *make_pipecmd(t_cmd *left, t_cmd *right)
{
    t_pipecmd   *cmd;

    cmd = malloc(sizeof(*cmd));
    ft_memset(cmd, 0, sizeof(*cmd));
    cmd->type = PIPE;
    cmd->left = left;
    cmd->right = right;
    return ((t_cmd *)cmd);
}

t_cmd	*make_redircmd(t_cmd *subcmd, char *file, int mode, int fd)
{
	t_redircmd	*rcmd;

	rcmd = malloc(sizeof(*rcmd));
	ft_memset(rcmd, 0, sizeof(*rcmd));
	rcmd->type = REDIR;
	rcmd->cmd = subcmd;
	rcmd->file = file;
	rcmd->mode = mode;
	rcmd->fd = fd;
	return ((t_cmd *)rcmd);
}
