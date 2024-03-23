/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:17:07 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/23 17:06:44 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Handles the SIGINT signal during heredoc input.
 * @param sig int: The signal number.
 */
static void	ft_sig_here(int sig)
{
	if (sig == SIGINT)
	{
		unlink(".file1.tmp");
		g_sig = 130;
	}
}

void	get_only_var(t_tok *tok, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && (str[i] != '$'))
		i++;
	tok->s_loc = i;
	get_var_name(tok, i, 1, str);
}

int	find_only_var(char *str)
{
	int	i;
	int	nd;

	i = 0;
	nd = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0'
			&& str[i + 1] != ' ' && str[i + 1] != '\"')
			nd++;
		i++;
	}
	return (nd);
}

/**
 * Combines strings around a variable expansion.
 * @param str char*: The original string.
 * @param tok t_tok*: Token containing variable location and length.
 * @param exp char*: The expansion of the variable.
 * @return char*: The new string with the variable expanded.
 */
static char	*frankenstein_nq(char *str, t_tok *tok, char *exp)
{
	char	*frank;
	char	*s1;
	char	*s2;

	s1 = ft_strdup(str);
	s1[tok->s_loc] = '\0';
	s2 = ft_strjoin(s1, exp);
	free (s1);
	s1 = ft_substr(str, tok->cut, (int)ft_strlen(str) - tok->cut);
	frank = ft_strjoin(s2, s1);
	free (s1);
	free (s2);
	return (frank);
}

char	*expand_only_var(char *str, t_shell *shell)
{
	t_tok	tok;
	char	*expansion;
	char	*frank;
	char	*temp;

	if (find_only_var(str) != 0)
	{
		get_only_var(&tok, str);
		expansion = get_expansion(&tok, shell);
		frank = frankenstein_nq(str, &tok, expansion);
		free(expansion);
		if (find_only_var(frank) != 0)
		{
			temp = expand_only_var(frank, shell);
			free (frank);
			frank = temp;
		}
		if (tok.str)
			free (tok.str);
		return (frank);
	}
	return (ft_strdup(str));
}

static char	*process_line(char *str, t_shell *shell)
{
	char	*temp;

	temp = expand_only_var(str, shell);
	ft_printf("expanded: %s\n", temp);
	free (str);
	str = temp;
	return (str);
}

/**
 * Executes the heredoc redirection.
 * @param rcmd t_redircmd*: The redirection command.
 * @param shell t_shell*: The shell instance.
 */
static void	ft_here(t_redircmd *rcmd, t_shell *shell)
{
	char	*line;
	int		fd;

	fd = open(".file1.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putendl_fd("minishell: error occured while opening file",
			STDERR_FILENO);
		exit(1);
	}
	signal(SIGINT, &ft_sig_here);
	while (1)
	{
		line = readline("heredoc> ");
		if (g_sig == 130)
		{
			close(fd);
			clean_exit(shell);
			exit(130);
		}
		if (line == NULL || ft_strcmp(line, rcmd->file) == 0)
			break ;
		line = process_line(line, shell);
		ft_putendl_fd(line, fd);
		if (line)
			free(line);
	}
	close(fd);
	close(rcmd->fd);
	unlink(".file1.tmp");
	clean_exit(shell);
	exit(0);
}

/**
 * Manages heredoc redirection by creating a temporary file.
 * @param rcmd t_redircmd*: The redirection command.
 * @param shell t_shell*: The shell instance.
 */
static void	ft_here_doc(t_redircmd *rcmd, t_shell *shell)
{
	int	status;

	rcmd->fd = open(".file1.tmp", O_RDONLY | O_CREAT | O_TRUNC, 0644);
	if (shell->in_fd != STDIN_FILENO && shell->in_fd != -1)
		close(shell->in_fd);
	shell->in_fd = rcmd->fd;
	if (shell->in_fd < 0)
		return ;
	signal(SIGQUIT, SIG_IGN);
	if (fork_child(shell) == 0)
		ft_here(rcmd, shell);
	waitpid(shell->pid, &status, 0);
	ft_signal_manager(2);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		shell->exit_status = 130;
	else
		shell->exit_status = WEXITSTATUS(status);
}

/**
 * Assists in managing different types of redirections.
 * @param rcmd t_redircmd*: The redirection command.
 * @param shell t_shell*: The shell instance.
 */
static void	ft_redir_helper(t_redircmd *rcmd, t_shell *shell)
{
	if (rcmd->mode == RIN && rcmd->file != NULL)
	{
		rcmd->fd = open(rcmd->file, O_RDONLY);
		if (shell->in_fd != STDIN_FILENO && shell->in_fd != -1)
			close(shell->in_fd);
		shell->in_fd = rcmd->fd;
	}
	else if (rcmd->mode == ROUT && rcmd->file != NULL)
	{
		rcmd->fd = open(rcmd->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (shell->out_fd != STDOUT_FILENO && shell->out_fd != -1)
			close(shell->out_fd);
		shell->out_fd = rcmd->fd;
	}
	else if (rcmd->mode == ROUTA && rcmd->file != NULL)
	{
		rcmd->fd = open(rcmd->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (shell->out_fd != STDOUT_FILENO && shell->out_fd != -1)
			close(shell->out_fd);
		shell->out_fd = rcmd->fd;
	}
	else if (rcmd->mode == RHERE)
		ft_here_doc(rcmd, shell);
}

/**
 * Manages redirection for a given command.
 * @param cmd t_cmd*: The command to manage redirection for.
 * @param env char**: The environment variables.
 * @param shell t_shell*: The shell instance.
 */
void	manage_redir(t_cmd *cmd, char **env, t_shell *shell)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	if (check_file(rcmd->file, shell) == 1)
		return ;
	ft_redir_helper(rcmd, shell);
	if (rcmd->fd < 0)
	{
		shell->exit_status = 1;
		ft_putendl_fd("open file error", STDERR_FILENO);
	}
	else
	{
		if (check_tree(rcmd->cmd, shell) == 0)
			run_exec(rcmd->cmd, env, shell);
		else
			reset_descriptors(shell);
	}
}
