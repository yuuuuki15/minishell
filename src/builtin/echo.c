/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:46:26 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/11 16:39:03 by ykawakit         ###   ########.fr       */
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
static void	ft_check_flag_echo(char *str, int *n_flg, int *i)
{
	int	j;

	j = 0;
	if (str != NULL && str[j] == '-')
	{
		while (str[++j] != '\0')
		{
			if (str[j] == 'n')
				*n_flg = 1;
			else
			{
				*n_flg = 0;
				return ;
			}
		}
		(*i)++;
	}
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
	i = 0;
	if (cmd->argv[1] != NULL && cmd->argv[1][0] == '-')
		ft_check_flag_echo(cmd->argv[1], &n_flg, &i);
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
