/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:34:14 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/02 16:27:24 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_update_environment(char *old_pwd, char *pwd)
{
	ft_add_env("OLDPWD", ft_strdup(old_pwd));
	ft_add_env("PWD", ft_strdup(pwd));
	return (0);
}

static int ft_change_directory(char *path)
{
	char	cwd[PATH_MAX];
	char	old_cwd[PATH_MAX];

	if (getcwd(old_cwd, PATH_MAX) == NULL)
		return (1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd(ERR_NO_SUCH_FILE_OR_DIRECTORY, STDERR_FILENO);
		ft_putendl_fd(path, STDERR_FILENO);
		return (1);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (ft_update_environment(old_cwd, cwd) != 0)
		return (1);
	return (0);
}

static int ft_handle_home_directory(void)
{
	t_env	*path;

	path = ft_get_env("HOME");
	if (!path)
	{
		ft_putendl_fd(ERR_HOME_NOT_FOUND, STDERR_FILENO);
		return (1);
	}
	return ft_change_directory(path->value);
}

static int ft_handle_oldpwd(void)
{
	t_env	*path;

	path = ft_get_env("OLDPWD");
	if (!path)
	{
		ft_putendl_fd(ERR_OLD_PATH_NOT_FOUND, STDERR_FILENO);
		return (1);
	}
	return ft_change_directory(path->value);
}

static int ft_handle_custom_path(t_execcmd *cmd)
{
	if (cmd->argv[2] != NULL)
	{
		ft_putstr_fd(ERR_STRING_NOT_IN_PWD, STDERR_FILENO);
		ft_putendl_fd(cmd->argv[1], STDERR_FILENO);
		return (1);
	}
	return ft_change_directory(cmd->argv[1]);
}

int cd(t_execcmd *cmd)
{
	if (cmd->argv[1] == NULL)
		return ft_handle_home_directory();
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
		return ft_handle_oldpwd();
	else
		return ft_handle_custom_path(cmd);
}
