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
void	clean_pipe(t_cmd *cmd)
{
	t_pipecmd	*pcmd;

	ft_printf("clean PIPE\n");
	pcmd = (t_pipecmd *)cmd;
	ft_printf("clean left\n");
	clean_tree(pcmd->left);
	ft_printf("clean right\n");
	clean_tree(pcmd->right);
}

// clean content of a redirect
void	clean_redir(t_cmd *cmd)
{
	t_redircmd	*rcmd;

	ft_printf("clean REDIR\n");
	rcmd = (t_redircmd *)cmd;
	free (rcmd->file);
	clean_tree(rcmd->cmd);
}

// clean content of an exec
void	clean_exec(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	int			i;

	ft_printf("clean EXEC\n");
	ecmd = (t_execcmd *)cmd;
	i = 0;
	while (ecmd->argv[i] != NULL)
	{
		free (ecmd->argv[i]);
		i++;
	}
	free (ecmd->argv);
}

// clean content of a back
void	clean_back(t_cmd *cmd)
{
	t_backcmd	*bcmd;

	bcmd = (t_backcmd *)cmd;
	ft_printf("clean BACK\n");
	clean_tree(bcmd->cmd);
}

// clean tree
void	clean_tree(t_cmd *cmd)
{
	if (cmd->type == EXEC)
	{
		clean_exec(cmd);
		free (cmd);
	}
	if (cmd->type == BACK)
		clean_back(cmd);
	if (cmd->type == PIPE)
		clean_pipe(cmd);
	if (cmd->type == REDIR)
		clean_redir(cmd);
}