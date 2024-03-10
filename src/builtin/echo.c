/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:46:26 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/10 19:28:34 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param cmd The command structure containing arguments passed to echo.
 * @return Always returns 0 to indicate success.
 *
 * Executes the echo command with or without the newline.
 */
int	ft_echo(t_execcmd *cmd)
{
	int	n_flg;
	int	i;

	n_flg = 0;
	i = 0;
	if (ft_strcmp(cmd->argv[1], "-n") == 0)
	{
		i++;
		n_flg = 1;
	}
	while (cmd->argv[++i] != NULL)
	{
		ft_printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1] != NULL)
			ft_printf(" ");
	}
	if (!n_flg)
		ft_printf("\n");
	return (0);
}
