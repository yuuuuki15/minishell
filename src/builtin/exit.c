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
	int	j;

	i = -1;
	j = 0;
	while (cmd->argv[j] != NULL)
	{
		if (j == 2 && cmd->argv[j] != NULL)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
		else if (j == 1 && cmd->argv[j] != NULL)
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
		shell->exit_prog = ft_atoi(cmd->argv[1]);
		}
		j++;
	}
	exit_shell(shell);
	return (0);
}
