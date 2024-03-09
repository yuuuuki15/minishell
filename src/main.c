/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/09 17:38:03 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_minishell_initializer(char **env, t_shell *g_shell)
{
	g_shell->user_input = NULL;
	g_shell->is_inside_pipe = 0;
	g_shell->pid = 0;
	g_shell->in_fd = STDIN_FILENO;
	g_shell->out_fd = STDOUT_FILENO;
	g_shell->stdin = dup(STDIN_FILENO);
	g_shell->stdout = dup(STDOUT_FILENO);
	g_shell->env = NULL;
	if (g_shell->stdin == -1 || g_shell->stdout == -1)
		return (1);
	// set_signals();
	ft_signal_manager();
	if (ft_init_env(env, g_shell) == 1)
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_shell	g_shell;
	int		do_exe;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	if (ft_minishell_initializer(env, &g_shell) == 1)
	{
		close(g_shell.stdin);
		close(g_shell.stdout);
		rl_clear_history();
		ft_clean_env(&g_shell);
		ft_error(ERR_INITIALIZE_MINISHELL);
	}
	while (1)
	{
		do_exe = get_data(&g_shell);
		if (do_exe)
		{
			cmd = lexer(g_shell.user_input, &g_shell);
			if (cmd != NULL)
				run_exec(cmd, env, &g_shell);
			clean_tree(cmd);
			if (g_shell.is_inside_pipe == 1)
				exit(0);
		}
	}
	//rl_clear_history(); //changed for home compiler
	clear_history();
	return (0);
}
