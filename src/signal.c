/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:35:34 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/01 15:36:51 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	printf("hello %d\n", sig);
}

void	ft_signal_manager(void)
{
	struct	sigaction	sa;

	sa.sa_handler = &ft_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &sa, NULL);
}
