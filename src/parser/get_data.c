/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:00:53 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/10 17:43:04 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exiting shell, free global variable
// should also free tree! Add this.
void	exit_shell(t_shell *shell)
{
	close(shell->stdin);
	close(shell->stdout);
	if (shell->user_input)
		free (shell->user_input);
	rl_clear_history();
	ft_clean_env(shell);
	ft_printf("%s", "Exiting shell\n");
	exit(0);
}

// use readline to display prompt and read in user input
// treat "exit" and ctrl-D but only when alone on line
// add non-blank lines to history
int	get_data(t_shell *shell)
{
	if (shell->user_input)
	{
		free (shell->user_input);
		shell->user_input = NULL;
	}
	shell->user_input = readline(PROMPT);
	if (ft_strchr(shell->user_input, EOF) != NULL)
	{
		ft_printf("this is control plus D handler \n");
	}
	if (!shell->user_input || ft_strcmp(shell->user_input, "exit") == 0)
	{
		if (!shell->user_input)
			ft_printf("NULL input %d\n", shell->pid);
		else if (ft_strcmp(shell->user_input, "exit") == 0)
			ft_printf("exiting due to exit command\n");
		exit_shell(shell);
	}
	if (ft_strlen(shell->user_input) > 0)
		add_history(shell->user_input);
	if (ft_strcmp(shell->user_input, "") == 0
		|| ft_strisspace(shell->user_input))
		return (0);
	else
	{
		ft_print_line(shell->user_input);
		return (1);
	}
	return (0);
}
