/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:34:14 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/02 15:06:15 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_home(t_execcmd *cmd)
{
	t_env	*path;

	path = ft_get_env("HOME");
	if (path == NULL)
		ft_putendl_fd(ERR_HOME_NOT_FOUND, STDERR_FILENO);
	if (chdir(path->value) == -1)
	{
		ft_putstr_fd(ERR_NO_SUCH_FILE_OR_DIRECTORY, STDERR_FILENO);
		ft_putendl_fd(path->value, STDERR_FILENO);
		return ;
	}
	ft_add_env("OLDPWD", ft_strdup((ft_get_env("PWD"))->value));
	ft_add_env("PWD", ft_strdup(cmd->argv[1]));
}

static void	ft_cd_oldpath(t_execcmd *cmd)
{
	t_env	*path;

	(void)cmd;
	path = ft_get_env("OLDPATH");
	if (path == NULL)
		ft_putendl_fd(ERR_OLD_PATH_NOT_FOUND, STDERR_FILENO);
	if (chdir(path->value) == -1)
	{
		ft_putstr_fd(ERR_NO_SUCH_FILE_OR_DIRECTORY, STDERR_FILENO);
		ft_putendl_fd(path->value, STDERR_FILENO);
		return ;
	}
	ft_add_env("OLDPATH", ft_strdup((ft_get_env("PWD"))->value));
	ft_add_env("PWD", ft_strdup(path->value));
}

void	cd(t_execcmd *cmd)
{
	if (cmd->argv[1] == NULL)
		return (ft_cd_home(cmd));
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
		return (ft_cd_oldpath(cmd));
	else if (cmd->argv[2] != NULL)
	{
		ft_putstr_fd(ERR_STRING_NOT_IN_PWD, STDERR_FILENO);
		ft_putendl_fd(cmd->argv[1], STDERR_FILENO);
		return ;
	}
	if (chdir(cmd->argv[1]) == -1)
	{
		ft_putstr_fd(ERR_NO_SUCH_FILE_OR_DIRECTORY, STDERR_FILENO);
		ft_putendl_fd(cmd->argv[1], STDERR_FILENO);
		return ;
	}
	ft_add_env(ft_strdup("PWD"), ft_strdup(cmd->argv[1]));
}
