/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:24:11 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/10 17:43:04 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// resets the prompt for readline
// clears line, puts you on a nel line and redisplays prompt
// void	reset_prompt(void)
// {
// 	write(2, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// controls behavior of ctrl-c (SIGINT) and ctrl-backslash (SIGQUIT)
// void	sig_test(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		reset_prompt();
// 	}
// 	if (signum == SIGQUIT)
// 	{
// 		close(shell->stdin);
// 		close(shell->stdout);
// 	}
// }

// void	set_signals(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = &sig_test;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }
