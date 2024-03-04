/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:14:00 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/04 09:14:14 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_pipe(t_cmd *cmd, char **env)
{
	t_pipecmd	*pcmd;
	int			p[2];

	pcmd = (t_pipecmd *)cmd;
	if (pipe(p) < 0)
	{
		ft_printf("Pipe error\n");
		exit(1);
	}
	if (fork_child() == 0)
	{
		//close(1);
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
		run_exec(pcmd->left, env);
	}
	if (fork_child() == 0)
	{
		close(0);
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		//close(p[1]);
		run_exec(pcmd->right, env);
	}
	close(p[1]);
	close(p[0]);
	wait(NULL);
	wait(NULL);
	exit(0);
}
