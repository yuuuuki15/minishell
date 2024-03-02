/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:36:26 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/01 18:04:47 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_execcmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0
		|| ft_strcmp(cmd->argv[0], "cd") == 0
		|| ft_strcmp(cmd->argv[0], "export") == 0
		|| ft_strcmp(cmd->argv[0], "unset") == 0
		|| ft_strcmp(cmd->argv[0], "env") == 0)
		return (1);
	else
		return (0);
}

void	ft_builtin_manager(t_execcmd *cmd)
{
	ft_printf("comand name: %s\n", cmd->argv[0]);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		cd(cmd);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		export(cmd);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		unset(cmd);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		env(cmd);
}