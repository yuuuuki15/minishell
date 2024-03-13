/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:46:26 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/13 14:26:12 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param char *str
 * @param int *n_flg
 * @param int *i
 *
 * this function will check flags for builtin command "echo".
*/
static int	ft_check_flag_echo(char *str, int *n_flg, int *i)
{
	int	j;

	j = 0;
	if (str != NULL && str[j] == '-')
	{
		while (str[++j] != '\0')
		{
			if (str[j] != 'n')
				return (1);
		}
		(*i)++;
	}
	*n_flg = 1;
	return (0);
}

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
	i = 1;
	while (cmd->argv[i] != NULL && cmd->argv[i][0] == '-')
	{
		if (ft_check_flag_echo(cmd->argv[i], &n_flg, &i))
			break ;
	}
	while (cmd->argv[i] != NULL)
	{
		ft_printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (!n_flg)
		ft_printf("\n");
	return (0);
}
