/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:35:34 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/12 15:27:56 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// resets the prompt for readline
// clears line, puts you on a nel line and redisplays prompt
static void	reset_prompt(void)
{
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
static void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		reset_prompt();
	}
}

/**
 * Sets up signal handlers for SIGINT, SIGQUIT, and SIGKILL.
 */
void	ft_signal_manager(void)
{
	signal(SIGINT, &ft_handler);
	signal(SIGQUIT, SIG_IGN);
}
