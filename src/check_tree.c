/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:55:48 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:54:57 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if the command is empty.
 * @param cmd t_cmd*: The command to check.
 * @return int: 1 if the command is empty, 0 otherwise.
 */
static int	check_cmd(t_cmd *cmd)
{
	t_execcmd	*out;
	int			ret;

	ret = 0;
	out = (t_execcmd *)cmd;
	if (out->argv[0] == NULL || ft_strcmp(out->argv[0], " ") == 0)
		ret = 1;
	return (ret);
}

/**
 * Checks the content of a list command.
 * @param cmd t_cmd*: The list command to check.
 * @param shell t_shell*: The shell environment.
 * @return int: 1 if there is an error in the list, 0 otherwise.
 */
static int	check_list2(t_cmd *cmd, t_shell *shell)
{
	t_listcmd	*lcmd;

	lcmd = (t_listcmd *)cmd;
	if (check_tree(lcmd->left, shell) == 1)
		return (1);
	if (check_tree(lcmd->right, shell) == 1)
		return (1);
	return (0);
}

/**
 * Checks the content of a redirect command.
 * @param cmd t_cmd*: The redirect command to check.
 * @param shell t_shell*: The shell environment.
 * @return int: 1 if there is an error in the redirect, 0 otherwise.
 */
static int	check_redir(t_cmd *cmd, t_shell *shell)
{
	t_redircmd	*rcmd;
	char		*temp;

	rcmd = (t_redircmd *)cmd;
	temp = ft_strtrim(rcmd->file, " ");
	if (ft_strcmp(temp, "") == 0)
	{
		ft_putendl_fd("bad token", STDERR_FILENO);
		free (temp);
		return (1);
	}
	free (temp);
	if (check_tree(rcmd->cmd, shell) == 1 && rcmd->mode != RHERE)
		return (1);
	return (0);
}

/**
 * Prints the structure of the tree following parsing.
 * @param cmd t_cmd*: The command tree to check.
 * @param shell t_shell*: The shell environment.
 * @return int: 1 if there is an error in the tree, 0 otherwise.
 */
int	check_tree(t_cmd *cmd, t_shell *shell)
{
	t_backcmd	*bcmd;
	int			ret;

	ret = 0;
	if (cmd == NULL)
		return (1);
	else if (cmd->type == EXEC)
		ret = check_cmd(cmd);
	else if (cmd->type == BACK)
	{
		bcmd = (t_backcmd *)cmd;
		ret = check_tree(bcmd->cmd, shell);
	}
	else if (cmd->type == PIPE || cmd->type == IFTHEN || cmd->type == IFOR)
		ret = check_list2(cmd, shell);
	else if (cmd->type == REDIR)
		ret = check_redir(cmd, shell);
	return (ret);
}
