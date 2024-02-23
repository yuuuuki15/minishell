/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/23 14:28:52 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * ENTRY POINT
*/
int	main(void)
{
	t_shell	shell;

	ft_init_env_path(&shell);
	while (1)
	{
		if ((shell.pid = fork()) == -1)
		{
			ft_putstr_fd(ERR_FORK, STDERR_FILENO);
			exit(1);
		}
		if (shell.pid == 0)
		{
			ft_printf("minishell %% ");
			shell.user_input = ft_get_next_line(STDIN_FILENO);
			shell.user_input = ft_strtrim(shell.user_input, "\n");
			if (ft_strcmp(shell.user_input, "exit") == 0)
			{
				kill(getppid(), SIGKILL);
				exit(0);
			}
			ft_exec(shell);
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}
