/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:36 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/20 22:32:36 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Unsets environment variables specified in the command arguments.
 *
 * @param cmd The command structure containing the arguments to unset.
 * @param shell The shell instance containing the environment variables.
 *
 * @return Always returns 0 to indicate success.
 */
int	ft_unset(t_execcmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (cmd->argv[++i])
	{
		ft_unset_env(cmd->argv[i], shell);
	}
	return (0);
}
