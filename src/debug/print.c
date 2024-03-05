/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:47:13 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/04 12:04:05 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print command with arguments
void	printcmd(t_cmd *cmd)
{
	int			i;
	t_execcmd	*out;

	out = (t_execcmd *)cmd;
	ft_printf("CMD: %s\n", out->argv[0]);
	i = 1;
	while (out->argv[i] != NULL)
	{
		if (i == 1)
			ft_printf("ARGS: ");
		ft_printf(".%s. ", out->argv[i]);
		i++;
	}
	if (i > 1)
		ft_printf("\n");
}

// print line of text
void	ft_print_line(char *line)
{
	ft_printf("read in:\t %s\n", line);
}

// print out structure of tree following parsing
void	print_tree(t_cmd *cmd)
{
	t_backcmd	*bcmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

	if (cmd->type == EXEC)
	{
		ft_printf("type: EXEC\n");
		printcmd(cmd);
	}
	if (cmd->type == BACK)
	{
		bcmd = (t_backcmd *)cmd;
		ft_printf("type: BACK\n");
		print_tree(bcmd->cmd);
	}
	if (cmd->type == PIPE)
	{
		ft_printf("type: PIPE\n");
		pcmd = (t_pipecmd *)cmd;
		ft_printf("left\n");
		print_tree(pcmd->left);
		ft_printf("right\n");
		print_tree(pcmd->right);
	}
	if (cmd->type == REDIR)
	{
		ft_printf("type: REDIR\n");
		rcmd = (t_redircmd *)cmd;
		printf("file: %s, mode: %d\n", rcmd->file, rcmd->mode);
		print_tree(rcmd->cmd);
	}
}
