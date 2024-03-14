/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:21:00 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/13 19:12:38 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_execcmd *cmd, t_shell *shell)
{
	int	i;

	i = -1;
	if (cmd->argv[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	else if (cmd->argv[1] != NULL)
	{
		while (cmd->argv[1][++i])
		{
			if (!ft_isdigit(cmd->argv[1][i]))
			{
				ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
				shell->exit_prog = 2;
				exit_shell(shell);
			}
		}
	}
	shell->exit_prog = ft_atoi(cmd->argv[1]);
	exit_shell(shell);
	return (0);
}
