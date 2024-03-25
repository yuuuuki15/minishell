/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/25 22:36:49 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

/**
 * Initializes the shell structure and global signal variable.
 * @param env char**: The environment variables.
 * @param shell t_shell*: The shell structure to initialize.
 * @return int: 0 on success, 1 on failure.
 * @error If duplicating file descriptors fails or initializing environment
 * variables fails, returns 1.
 */
static int	ft_minishell_initializer(char **env, t_shell *shell)
{
	shell->user_input = NULL;
	shell->is_inside_pipe = 0;
	shell->pid = 0;
	shell->in_fd = STDIN_FILENO;
	shell->out_fd = STDOUT_FILENO;
	shell->env = NULL;
	shell->exit_status = 0;
	shell->head_cmd = NULL;
	g_sig = 0;
	if (ft_init_env(env, shell) == 1)
		return (1);
	return (0);
}

/**
 * Resets the shell to its initial state and prints an error message.
 * @param shell t_shell*: The shell structure to reset.
 * No return value.
 */
void	reset_minishell(t_shell *shell)
{
	rl_clear_history();
	ft_clean_env(shell);
	ft_error(ERR_INITIALIZE_MINISHELL);
}

// check if there are input arguments
static int	input_error(int ac, char **av)
{
	if (ac > 1)
	{
		ft_putendl_fd("Error: minishell does not take arguments",
			STDERR_FILENO);
		return (1);
	}
	(void)av;
	return (0);
}

/**
 * The main loop of the minishell program.
 * @param ac int: The count of arguments.
 * @param av char**: The argument values.
 * @param env char**: The environment variables.
 * @return int: Always returns 0.
 * Initializes the shell, processes user input, and executes commands until
 * the program is exited.
 */
int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	t_cmd	*cmd;

	if (input_error(ac, av) == 1)
		exit (1);
	if (ft_minishell_initializer(env, &shell) == 1)
		reset_minishell(&shell);
	while (1)
	{
		if (get_data(&shell))
		{
			cmd = lexer(shell.user_input, &shell);
			if (cmd != NULL)
			{
				shell.head_cmd = cmd;
				ft_reset_fd(&shell);
				run_exec(cmd, env, &shell);
			}
			clean_tree(cmd);
			if (shell.is_inside_pipe == 1)
				exit(0);
		}
	}
	exit_shell(&shell);
	return (0);
}
