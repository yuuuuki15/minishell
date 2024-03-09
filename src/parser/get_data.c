/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:00:53 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/09 17:09:57 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exiting shell, free global variable
// should also free tree! Add this.
void	exit_shell(t_shell *g_shell)
{
	close(g_shell->stdin);
	close(g_shell->stdout);
	if (g_shell->user_input)
		free (g_shell->user_input);
	rl_clear_history();
	ft_clean_env(g_shell);
	ft_printf("%s", "Exiting shell\n");
	exit(0);
}

// use readline to display prompt and read in user input
// treat "exit" and ctrl-D but only when alone on line
// add non-blank lines to history
int	get_data(t_shell *g_shell)
{
	if (g_shell->user_input)
	{
		free (g_shell->user_input);
		g_shell->user_input = NULL;
	}
	g_shell->user_input = readline(PROMPT);
	if (ft_strchr(g_shell->user_input, EOF) != NULL)
	{
		ft_printf("this is control plus D handler \n");
	}
	if (!g_shell->user_input || ft_strcmp(g_shell->user_input, "exit") == 0)
	{
		if (!g_shell->user_input)
			ft_printf("NULL input %d\n", g_shell->pid);
		else if (ft_strcmp(g_shell->user_input, "exit") == 0)
			ft_printf("exiting due to exit command\n");
		exit_shell(g_shell);
	}
	if (ft_strlen(g_shell->user_input) > 0)
		add_history(g_shell->user_input);
	if (ft_strcmp(g_shell->user_input, "") == 0
		|| ft_strisspace(g_shell->user_input))
		return (0);
	else
	{
		ft_print_line(g_shell->user_input);
		return (1);
	}
	return (0);
}
