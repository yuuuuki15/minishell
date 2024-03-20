/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:21:00 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/20 11:38:47 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set exit tag if one argument, raise error if non-numeric
static void	exit_one_arg(t_execcmd *cmd, t_shell *shell)
{
	int	i;

	i = -1;
	while (cmd->argv[1][++i])
	{
		if (cmd->argv[1][i] == '+' || cmd->argv[1][i] == '-')
			i++;
		if (!ft_isdigit(cmd->argv[1][i]))
		{
			ft_putendl_fd("minishell: exit: numeric argument required",
				STDERR_FILENO);
			shell->exit_prog = 2;
			exit_shell(shell);
		}
	}
	shell->exit_prog = ft_atoi(cmd->argv[1]);
}

// exit program
// if too many arguments raise error
int	ft_exit(t_execcmd *cmd, t_shell *shell)
{
	int	j;

	j = 0;
	while (cmd->argv[j] != NULL)
	{
		if (j == 2 && cmd->argv[j] != NULL)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
		else if (j == 1 && cmd->argv[j] != NULL)
			exit_one_arg(cmd, shell);
		j++;
	}
	exit_shell(shell);
	return (0);
}
