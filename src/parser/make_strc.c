/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_strc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:23:56 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:44:25 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Allocates and initializes an executable command structure.
 * @return t_cmd*: Pointer to the newly created command structure.
 * @error Returns NULL if memory allocation fails.
 */
t_cmd	*make_execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

/**
 * Creates a background command structure wrapping a subcommand.
 * @param subcmd t_cmd*: The subcommand to be executed in the background.
 * @return t_cmd*: Pointer to the newly created background command structure.
 * @error Returns NULL if memory allocation fails.
 */
t_cmd	*make_backcmd(t_cmd *subcmd)
{
	t_backcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = BACK;
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}

/**
 * Creates a list command structure holding pointers to left and right commands.
 * @param left t_cmd*: The left command in the list.
 * @param right t_cmd*: The right command in the list.
 * @param type int: The type of list command.
 * @return t_cmd*: Pointer to the newly created list command structure.
 * @error Returns NULL if memory allocation fails.
 */
t_cmd	*make_listcmd(t_cmd *left, t_cmd *right, int type)
{
	t_listcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = type;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

/**
 * Creates a redirect command structure containing filename and redirection type.
 * @param subcmd t_cmd*: The subcommand to apply redirection to.
 * @param file char*: The filename for redirection.
 * @param mode int: The mode of redirection (e.g., input, output).
 * @return t_cmd*: Pointer to the newly created redirect command structure.
 * @error Returns NULL if memory allocation fails.
 */
t_cmd	*make_redircmd(t_cmd *subcmd, char *file, int mode)
{
	t_redircmd	*rcmd;

	rcmd = malloc(sizeof(*rcmd));
	if (rcmd == NULL)
		return (NULL);
	rcmd->type = REDIR;
	rcmd->cmd = subcmd;
	if (file != NULL)
		rcmd->file = ft_strdup(file);
	if (file)
		free (file);
	rcmd->mode = mode;
	rcmd->fd = -1;
	return ((t_cmd *)rcmd);
}
