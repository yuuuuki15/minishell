/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:35:34 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/01 16:03:06 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param sig The signal number.
 *
 * Handles the SIGINT signal by printing a newline and the prompt.
 * Linux: Ctrl + C
 */
static void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
	}
}

/**
 * @param sig The signal number.
 *
 * Ignores the received signal.
 * Linux: Ctrl + \
 */
static void	ft_ignore_signal(int sig)
{
	(void)sig;
}

/**
 * @param sig The signal number.
 *
 * Exits the program when SIGKILL is received.
 * Linux: Ctrl + D
 * Mac: Ctrl + Z
 */
static void	ft_exit_program(int sig)
{
	// it doesn't work for now. I think signal is not SIGKILL...
	if (sig == SIGKILL)
	{
		ft_putstr_fd("exit minishell\n", STDOUT_FILENO);
		exit(0);
	}
}

/**
 * Sets up signal handlers for SIGINT, SIGQUIT, and SIGKILL.
 */
void	ft_signal_manager(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_exit;

	sa_int.sa_handler = ft_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = ft_ignore_signal;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
	sa_exit.sa_handler = ft_exit_program;
	sigemptyset(&sa_exit.sa_mask);
	sa_exit.sa_flags = SA_RESTART;
	sigaction(SIGKILL, &sa_exit, NULL);
}
