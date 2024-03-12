/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:35:34 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/12 17:36:30 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// resets the prompt for readline
// clears line, puts you on a nel line and redisplays prompt
static void	reset_prompt(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * @param sig The signal number.
 *
 * Handles the SIGINT signal by printing a newline and the prompt.
 * Linux: Ctrl + C
 */
static void	ft_sig_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
	}
}

static void	ft_sig_backslash(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	}
}

/**
 * Sets up signal handlers for SIGINT, SIGQUIT, and SIGKILL.
 */
void	ft_signal_manager(int option)
{
	if (option == 1)
	{
		signal(SIGINT, &reset_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == 2)
	{
		signal(SIGINT, &ft_sig_c);
		signal(SIGQUIT, &ft_sig_backslash);
	}
}
