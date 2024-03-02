/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:45 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/02 17:52:22 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @param cmd The command structure containing the env command.
 * @return Always returns 0 to indicate success.
 *
 * Executes the env command which prints the current environment variables.
 */
int	env(t_execcmd *cmd)
{
	(void)cmd;
	ft_show_env();
	return (0);
}
