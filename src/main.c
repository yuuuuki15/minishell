/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/09 12:31:34 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell;

static int	ft_minishell_initializer(char **env)
{
	g_shell = malloc(sizeof(t_shell));
	if (g_shell == NULL)
		return (1);
	ft_memset(g_shell, '\0', sizeof(t_shell));
	g_shell->user_input = NULL;
	g_shell->is_inside_pipe = 0;
	g_shell->in_fd = STDIN_FILENO;
	g_shell->out_fd = STDOUT_FILENO;
	g_shell->stdin = dup(STDIN_FILENO);
	g_shell->stdout = dup(STDOUT_FILENO);
	if (g_shell->stdin == -1 || g_shell->stdout == -1)
		return (1);
	set_signals();
	if (ft_init_env(env) == 1)
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int		do_exe;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	if (ft_minishell_initializer(env) == 1)
		ft_error(ERR_INITIALIZE_MINISHELL);
	while (1)
	{
		do_exe = get_data();
		if (do_exe)
		{
			cmd = lexer(g_shell->user_input);
			if (cmd != NULL)
				run_exec(cmd, env);
			clean_tree(cmd);
			if (g_shell->is_inside_pipe == 1)
				exit(0);
		}
	}
	rl_clear_history();
	return (0);
}
