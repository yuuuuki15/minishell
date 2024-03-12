/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:45 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/12 16:37:43 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param cmd The command structure containing the env command.
 * @return Always returns 0 to indicate success.
 *
 * Executes the env command which prints the current environment variables.
 */
int	ft_env(t_execcmd *cmd, t_shell *shell)
{
	(void)cmd;
	if (cmd->argv[1] != NULL)
	{
		if (cmd->argv[1][0] == '-')
			ft_putendl_fd(ERR_OPTION_NOT_SUPPORTED, STDERR_FILENO);
		else
			ft_putendl_fd(ERR_ARGUMENT_NOT_SUPPORTED, STDERR_FILENO);
		return (1);
	}
	ft_show_env(shell);
	return (0);
}
