/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:00:53 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 16:52:23 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Cleans up resources before exiting the shell.
 * @param shell t_shell*: The shell instance.
 */
void	clean_exit(t_shell *shell)
{
	close(shell->stdin);
	close(shell->stdout);
	if (shell->user_input)
		free (shell->user_input);
	rl_clear_history();
	ft_clean_env(shell);
	if (shell->head_cmd)
		clean_tree(shell->head_cmd);
}

/**
 * Exits the shell and frees global variables.
 * @param shell t_shell*: The shell instance.
 */
void	exit_shell(t_shell *shell)
{
	clean_exit(shell);
	exit(shell->exit_prog);
}

int	ft_get_input(t_shell *shell)
{
	char	*tmp;

	if (!isatty(STDIN_FILENO))
	{
		shell->user_input = NULL;
		tmp = ft_get_next_line(STDIN_FILENO);
		if (tmp)
		{
			shell->user_input = ft_substr(tmp, 0, (ft_strlen(tmp) - 1));
			free(tmp);
		}
		if (shell->user_input == NULL)
			return (1);
		return (0);
	}
	else
	{
		shell->user_input = readline(PROMPT);
		return (0);
	}
}

/**
 * Displays a prompt and reads user input using readline.
 * Treats "exit" and ctrl-D but only when alone on a line.
 * Adds non-blank lines to history.
 * @param shell t_shell*: The shell instance.
 * @return int: 1 if input is not empty or only whitespace, 0 otherwise.
 * @error Returns 0 if an error occurs or if input is empty or only whitespace.
 */
int	get_data(t_shell *shell)
{
	ft_signal_manager(1);
	if (shell->user_input)
	{
		free (shell->user_input);
		shell->user_input = NULL;
	}
	if (ft_get_input(shell) == 1)
	{
		shell->head_cmd = NULL;
		exit_shell(shell);
	}
	if (g_sig != 0)
		shell->exit_status = g_sig;
	g_sig = 0;
	if (!shell->user_input)
	{
		shell->head_cmd = NULL;
		exit_shell(shell);
	}
	if (ft_strlen(shell->user_input) > 0)
		add_history(shell->user_input);
	if (ft_strcmp(shell->user_input, "") == 0
		|| ft_strisspace(shell->user_input))
		return (0);
	else
		return (1);
	return (0);
}
