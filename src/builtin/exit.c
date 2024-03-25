/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:21:00 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/25 21:04:20 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Sets the exit status of the shell if one argument is provided. If the
 * argument is non-numeric, it raises an error and exits the shell.
 * @param cmd t_execcmd*: The command structure containing the arguments.
 * @param shell t_shell*: The shell instance to set the exit status for.
 */
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
			ft_putendl_fd(ERR_EXIT_NUMERIC_REQUIRED, STDERR_FILENO);
			shell->exit_status = 2;
			exit_shell(shell);
		}
	}
	shell->exit_status = ft_atoi(cmd->argv[1]);
}

/**
 * Exits the program. If more than one argument is provided, it raises an error.
 * @param cmd t_execcmd*: The command structure containing the arguments.
 * @param shell t_shell*: The shell instance to exit from.
 * @return int: Returns 1 if too many arguments are provided, otherwise 0.
 * Error cases: Returns 1 if more than one argument is provided.
 */
int	ft_exit(t_execcmd *cmd, t_shell *shell)
{
	int	j;

	j = 0;
	while (cmd->argv[j] != NULL)
	{
		if (j == 2 && cmd->argv[j] != NULL)
		{
			ft_putendl_fd(ERR_EXIT_TOO_MANY_ARGUMENTS, STDERR_FILENO);
			return (1);
		}
		else if (j == 1 && cmd->argv[j] != NULL)
			exit_one_arg(cmd, shell);
		j++;
	}
	exit_shell(shell);
	return (0);
}
