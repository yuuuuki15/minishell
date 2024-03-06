/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/06 13:25:15 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell;

int	main(int ac, char **av, char **env)
{
	int		do_exe;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	g_shell = malloc(sizeof(t_shell));
	if (g_shell == NULL)
		return (1);
	set_signals();
	ft_init_env(env);
	while (1)
	{
		do_exe = get_data();
		if (do_exe)
		{
			cmd = lexer(g_shell->user_input);
			if (cmd != NULL)
				run_exec(cmd, env);
			if (g_shell->is_inside_pipe == 1)
				exit(0);
		}
	}
	rl_clear_history();
	return (0);
}
