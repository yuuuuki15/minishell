/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:55:48 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/07 12:57:00 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// clean content of a pipe
void	clean_list(t_cmd *cmd)
{
	t_listcmd	*lcmd;

	lcmd = (t_listcmd *)cmd;
	clean_tree(lcmd->left);
	clean_tree(lcmd->right);
	free (lcmd);
}

// clean content of a redirect
void	clean_redir(t_cmd *cmd)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	free (rcmd->file);
	if (rcmd->fd != -1)
		close(rcmd->fd);
	clean_tree(rcmd->cmd);
	free (rcmd);
}

// clean content of an exec
void	clean_exec(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	int			i;

	if (cmd == NULL)
		return ;
	ecmd = (t_execcmd *)cmd;
	if (ecmd->argv == NULL)
	{
		free (ecmd);
		return ;
	}
	else
	{
		i = 0;
		while (ecmd->argv[i] != NULL)
		{
			free (ecmd->argv[i]);
			i++;
		}
		free (ecmd->argv);
	}
	free (ecmd);
}

// clean content of a back
void	clean_back(t_cmd *cmd)
{
	t_backcmd	*bcmd;

	bcmd = (t_backcmd *)cmd;
	clean_tree(bcmd->cmd);
	free (bcmd);
}

// clean tree
void	clean_tree(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->type == EXEC)
		clean_exec(cmd);
	else if (cmd->type == BACK)
		clean_back(cmd);
	else if (cmd->type == PIPE || cmd->type == IFTHEN || cmd->type == IFOR)
		clean_list(cmd);
	else if (cmd->type == REDIR)
		clean_redir(cmd);
}
