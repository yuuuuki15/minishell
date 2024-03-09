/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:02:54 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/04 12:01:40 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_back(t_cmd *cmd, char **env)
{
	t_backcmd	*bcmd;

	bcmd = (t_backcmd *)cmd;
	ft_printf("Background jobs not supported.");
	ft_printf(" Running command in foreground.\n");
	run_exec(bcmd->cmd, env);
}

void	manage_andor(t_cmd *cmd, char **env)
{
	t_listcmd	*lcmd;

	lcmd = (t_listcmd *)cmd;

	run_exec(lcmd->left, env);
	if (g_shell->exit_status == 0 && cmd->type == IFTHEN)
	{
		ft_printf("exit status %d\n", g_shell->exit_status);
		run_exec(lcmd->right, env);
	}
	else if (g_shell->exit_status == 1 && cmd->type == IFOR)
	{
		ft_printf("exit status %d\n", g_shell->exit_status);
		run_exec(lcmd->right, env);
	}
}
