/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:35:34 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/20 22:55:21 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

/**
 * Resets the prompt for readline, clears line, puts you on a new line, and
 * redisplays prompt.
 * @param sig int: The signal number.
 */
static void	reset_prompt(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig = 130;
}

/**
 * Handles the SIGINT signal by printing a newline.
 * @param sig int: The signal number. Only acts on SIGINT.
 */
static void	ft_sig_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
	}
}

/**
 * Handles the SIGQUIT signal by printing "Quit (core dumped)" to STDERR.
 * @param sig int: The signal number. Only acts on SIGQUIT.
 */
static void	ft_sig_backslash(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	}
}

/**
 * Sets up signal handlers for SIGINT and SIGQUIT based on the given option.
 * @param option int: Determines the set of signal handlers to use.
 *                   1 for reset_prompt and ignore SIGQUIT,
 *                   2 for custom SIGINT and SIGQUIT handlers.
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
