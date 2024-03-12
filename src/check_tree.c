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

// check for NULL command
int	check_cmd(t_cmd *cmd)
{
	t_execcmd	*out;
	int			ret;

	ret = 0;
	out = (t_execcmd *)cmd;
	if (out->argv[0] == NULL)
		ret = 1;
	return (ret);
}

// check content of a list
void	check_list2(t_cmd *cmd, t_shell *shell)
{
	t_listcmd	*lcmd;

	lcmd = (t_listcmd *)cmd;
	check_tree(lcmd->left, shell);
	check_tree(lcmd->right, shell);
}

// check content of a redirect
void	check_redir(t_cmd *cmd, t_shell *shell)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	check_tree(rcmd->cmd, shell);
}

// print out structure of tree following parsing
int	check_tree(t_cmd *cmd, t_shell *shell)
{
	t_backcmd	*bcmd;
	int			ret;

	ret = 0;
	if (cmd->type == EXEC)
	{
		ret = check_cmd(cmd);
		if (ret == 1)
		{
			shell->exit_status = 2;
			return (ret);
		}
	}
	if (cmd->type == BACK)
	{
		bcmd = (t_backcmd *)cmd;
		check_tree(bcmd->cmd, shell);
	}
	if (cmd->type == PIPE || cmd->type == IFTHEN || cmd->type == IFOR)
		check_list2(cmd, shell);
	if (cmd->type == REDIR)
		check_list2(cmd, shell);
	return (0);
}
