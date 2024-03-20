/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:55:48 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:56:01 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Cleans the content of a pipe command.
 * @param cmd t_cmd*: The command structure to clean.
 */
static void	clean_list(t_cmd *cmd)
{
	t_listcmd	*lcmd;

	lcmd = (t_listcmd *)cmd;
	clean_tree(lcmd->left);
	clean_tree(lcmd->right);
	free (lcmd);
}

/**
 * Cleans the content of a redirect command.
 * @param cmd t_cmd*: The command structure to clean.
 */
static void	clean_redir(t_cmd *cmd)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	free (rcmd->file);
	if (rcmd->fd != -1)
		close(rcmd->fd);
	clean_tree(rcmd->cmd);
	free (rcmd);
}

/**
 * Cleans the content of an exec command.
 * @param cmd t_cmd*: The command structure to clean.
 */
static void	clean_exec(t_cmd *cmd)
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

/**
 * Cleans the content of a back command.
 * @param cmd t_cmd*: The command structure to clean.
 */
static void	clean_back(t_cmd *cmd)
{
	t_backcmd	*bcmd;

	bcmd = (t_backcmd *)cmd;
	clean_tree(bcmd->cmd);
	free (bcmd);
}

/**
 * Cleans the command tree recursively.
 * @param cmd t_cmd*: The root command structure to start cleaning from.
 */
void	clean_tree(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	else if (cmd->type == EXEC)
		clean_exec(cmd);
	else if (cmd->type == BACK)
		clean_back(cmd);
	else if (cmd->type == PIPE || cmd->type == IFTHEN || cmd->type == IFOR)
		clean_list(cmd);
	else if (cmd->type == REDIR)
		clean_redir(cmd);
}
