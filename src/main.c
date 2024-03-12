/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/12 17:14:49 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_minishell_initializer(char **env, t_shell *shell)
{
	shell->user_input = NULL;
	shell->is_inside_pipe = 0;
	shell->pid = 0;
	shell->in_fd = STDIN_FILENO;
	shell->out_fd = STDOUT_FILENO;
	shell->stdin = dup(STDIN_FILENO);
	shell->stdout = dup(STDOUT_FILENO);
	shell->env = NULL;
	if (shell->stdin == -1 || shell->stdout == -1)
		return (1);
	if (ft_init_env(env, shell) == 1)
		return (1);
	return (0);
}

void	reset_minishell(t_shell *shell)
{
	close(shell->stdin);
	close(shell->stdout);
	rl_clear_history();
	ft_clean_env(shell);
	ft_error(ERR_INITIALIZE_MINISHELL);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	if (ft_minishell_initializer(env, &shell) == 1)
		reset_minishell(&shell);
	while (1)
	{
		if (get_data(&shell))
		{
			cmd = lexer(shell.user_input, &shell);
			if (cmd != NULL)
			{
				if (check_tree(cmd, &shell) == 0)
					run_exec(cmd, env, &shell);
				clean_tree(cmd);
			}
			if (shell.is_inside_pipe == 1)
				exit(0);
		}
	}
	rl_clear_history();
	return (0);
}
