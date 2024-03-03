#include "minishell.h"

void	manage_redir(t_cmd *cmd, char **env)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	close(rcmd->fd);
	rcmd->fd = open(rcmd->file, rcmd->mode);
	ft_printf("fd: %d\n", rcmd->fd);
	if (rcmd->fd < 0)
	{
		ft_printf("open file error, clean this up!\n");
		exit(1);
	}
	// for redirect input
	if (rcmd->mode == O_RDONLY)
		dup2(rcmd->fd, 0);
	free(rcmd->file);
	ft_printf("This executes but results in a seg fault\n");
	run_exec(rcmd->cmd, env);
}
