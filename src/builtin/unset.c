/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:36 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/02 18:06:12 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param t_execcmd* cmd
 * @return int status_code
 *
 * This function takes a command structure and finds the matching
 * environment variable and unset it
*/
int	unset(t_execcmd *cmd)
{
	int	i;

	(void)cmd;
	(void)shell;
	i = 0;
	while (cmd->argv[++i])
	{
		ft_unset_env(cmd->argv[i]);
	}
	return (0);
}
