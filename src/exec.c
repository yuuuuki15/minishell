/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:41:30 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/23 13:23:12 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_env_path(t_shell *shell)
		{
			shell->env_path = ft_split(getenv("PATH"), ':');
			if (shell->env_path == NULL)
				exit(1);
			}

char	*ft_get_path(t_shell shell)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = -1;
	while (shell.env_path[++i])
	{
		temp = ft_strjoin(shell.env_path[i], "/");
		full_path = ft_strjoin(temp, shell.user_input);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

void	ft_exec(t_shell shell)
{
	char	**cmd_array;
	char	*pathname;
	int		res;

	cmd_array = ft_split(shell.user_input, ' ');
	pathname = ft_get_path(shell);

	// int len = ft_strlen(pathname);
	// if (pathname[len - 1] == '\n')
	// 	pathname[len - 1] = '\0';

	ft_printf("pathname: %s\n", pathname);
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
