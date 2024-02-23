/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:41:30 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/23 14:28:26 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @param t_shell* shell
 *
 * This function will initialize environment path of the system.
 * And put them in shell->env_path.
*/
void	ft_init_env_path(t_shell *shell)
{
	shell->env_path = ft_split(getenv("PATH"), ':');
	if (shell->env_path == NULL)
		exit(1);
}

/**
 * @param t_shell shell
 * @param char* cmd
 *
 * @return char* fullpath
 *
 * This function takes user input and try to execute with every
 * environment path. Return fullpath on success.
*/
char	*ft_get_path(t_shell shell, char *cmd)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = -1;
	while (shell.env_path[++i])
	{
		temp = ft_strjoin(shell.env_path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

/**
 * @param t_shell shell
 *
 * This function takes user input and convert into executive command then
 * execute them. Print error message when error occurs.
*/
void	ft_exec(t_shell shell)
{
	char	**cmd_array;
	char	*pathname;
	int		res;

	cmd_array = ft_split(shell.user_input, ' ');
	pathname = ft_get_path(shell, cmd_array[0]);
	res = execve(pathname, cmd_array, NULL);
	if (res < 0)
	{
		if (pathname != NULL)
			free(pathname);
		ft_putstr_fd(ERR_COMMAND_NOT_FOUND, STDERR_FILENO);
		ft_putendl_fd(cmd_array[0], STDERR_FILENO);
		ft_free_tab(cmd_array);
		exit(errno);
	}
}
