/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:02:54 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 11:50:48 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_back(t_cmd *cmd, char **env, t_shell *shell)
{
	t_backcmd	*bcmd;

	bcmd = (t_backcmd *)cmd;
	ft_putendl_fd(ERR_BACKGROUND_NOT_SUPPORTED, STDERR_FILENO);
	run_exec(bcmd->cmd, env, shell);
}

void	manage_andor(t_cmd *cmd, char **env, t_shell *shell)
{
	t_listcmd	*lcmd;

	lcmd = (t_listcmd *)cmd;
	run_exec(lcmd->left, env, shell);
	if (shell->exit_status == 0 && cmd->type == IFTHEN)
		run_exec(lcmd->right, env, shell);
	else if (shell->exit_status != 0 && cmd->type == IFOR)
		run_exec(lcmd->right, env, shell);
}
