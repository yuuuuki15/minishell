/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:00:53 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/06 10:43:45 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exiting shell, free global variable
// should also free tree! Add this.
void	exit_shell(void)
{
	free (g_shell->user_input);
	//rl_clear_history(); //changed for home compiler
	clear_history();
	ft_printf("%s", "Exiting shell\n");
	exit(0);
}

// use readline to display prompt and read in user input
// treat "exit" and ctrl-D but only when alone on line
// add non-blank lines to history
int	get_data(void)
{
	if (g_shell->user_input)
	{
		free (g_shell->user_input);
		g_shell->user_input = NULL;
	}
	g_shell->user_input = readline(PROMPT);
	if (!g_shell->user_input || ft_strcmp(g_shell->user_input, "exit") == 0)
	{
		if (!g_shell->user_input)
			ft_printf("NULL input %d\n", g_shell->pid);
		if (ft_strcmp(g_shell->user_input, "exit") == 0)
			ft_printf("exiting due to exit command\n");
		exit_shell();
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
