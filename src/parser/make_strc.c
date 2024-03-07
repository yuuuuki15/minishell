/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_strc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:23:56 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/04 09:19:38 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// stores information for an executable command
t_cmd	*make_execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

// essentially strips the ampersand and passes cmd, in bash after & is like a pipe
t_cmd	*make_backcmd(t_cmd *subcmd)
{
	t_backcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = BACK;
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}

// makes a pipe com holding pointers to left and right comds in pipe
t_cmd	*make_pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

// makes a redirect cmd containing filename and type of redir
t_cmd	*make_redircmd(t_cmd *subcmd, char *file, int mode)
{
	t_redircmd	*rcmd;

	rcmd = malloc(sizeof(*rcmd));
	ft_memset(rcmd, 0, sizeof(*rcmd));
	rcmd->type = REDIR;
	rcmd->cmd = subcmd;
	rcmd->file = file;
	rcmd->mode = mode;
	rcmd->fd = -1;
	return ((t_cmd *)rcmd);
}
