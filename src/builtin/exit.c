/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:21:00 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/19 10:03:24 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit program
// if too many arguments raise error
int	ft_exit(t_execcmd *cmd, t_shell *shell)
{
	int	i;

	i = -1;
	if (cmd->argv[1][0] == '+' || cmd->argv[1][0] == '-')
		i++;
	while (cmd->argv[1][++i])
	{
		if (!ft_isdigit(cmd->argv[1][i]))
		{
			ft_putendl_fd(ERR_EXIT_NUMERIC_REQUIRED, STDERR_FILENO);
			shell->exit_prog = 2;
			exit_shell(shell);
		}
	}
	if (cmd->argv[2] != NULL)
	{
		ft_putendl_fd(ERR_EXIT_TOO_MANY_ARGUMENTS, STDERR_FILENO);
		return (1);
	}
	shell->exit_prog = ft_atoi(cmd->argv[1]);
	exit_shell(shell);
	return (1);
}
