/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/02 16:31:07 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*shell;

int	main(int ac, char **av, char **env)
{
	int		do_exe;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		return (1);
	set_signals();
	shell->sig = 1;
	ft_init_env(env);
	// ft_signal_manager();
	while (1)
	{
		do_exe = get_data();
		if (do_exe && shell->sig == 1)
		{
			cmd = lexer(shell->user_input);
			run_exec(cmd, env); //passing env to exeutor so that commands like clear work
		}
		shell->sig = 1;
	}
	clear_history();
	return (0);
}
