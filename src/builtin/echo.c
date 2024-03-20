/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:46:26 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/20 22:25:34 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks for the presence of '-n' flag in the echo command.
 * @param str char*: The string to check for '-n' flag.
 * @param n_flg int*: Pointer to flag indicating presence of '-n'.
 * @param i int*: Pointer to index in argv array.
 * @return int: Returns 0 if '-n' flag is present, 1 otherwise.
 * Error cases: None.
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
 * Executes the echo command, printing arguments to standard output.
 * @param cmd t_execcmd*: The command structure containing arguments.
 * @return int: Always returns 0 to indicate success.
 * Error cases: None.
 * Executes the echo command with or without the newline based on '-n' flag.
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
