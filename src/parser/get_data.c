/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:00:53 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/13 18:58:54 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// exiting shell, free global variable
void	exit_shell(t_shell *shell)
{
	clean_exit(shell);
	ft_printf("%s", "Exiting shell\n");
	exit(shell->exit_prog);
}

// use readline to display prompt and read in user input
// treat "exit" and ctrl-D but only when alone on line
// add non-blank lines to history
int	get_data(t_shell *shell)
{
	ft_signal_manager(1);
	if (shell->user_input)
	{
		free (shell->user_input);
		shell->user_input = NULL;
	}
	shell->user_input = readline(PROMPT);
	if (!shell->user_input)
	{
		ft_printf("NULL input %d\n", shell->pid);
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
