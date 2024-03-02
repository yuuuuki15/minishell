/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:24 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/02 17:37:33 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_add_or_update_env(char *arg)
{
    char *key;
    char *value;
    int equal_pos;

    equal_pos = ft_strchr(arg, '=') - arg;
    if (equal_pos < 0)
    {
		if (ft_is_valid_identifier(arg))
		{
			if (ft_get_env(arg) != NULL)
				return (0);
			ft_add_env(ft_strdup(arg), strdup(""));
			return (0);
		}
        ft_putstr_fd("export: '", STDERR_FILENO);
        ft_putstr_fd(arg, STDERR_FILENO);
        ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
        return (1);
    }
    if ((key = ft_get_key(arg)) == NULL)
		return (1);
    if ((value = ft_get_value(arg)) == NULL)
	{
		free(key);
		return (1);
	}
    ft_add_env(key, value);
    return (0);
}

int	export(t_execcmd *cmd)
{
	int i;
	int status;

	if (cmd->argv[1] == NULL)
	{
		ft_show_env();
		return (0);
	}
	i = 0;
	status = 0;
	while (cmd->argv[++i])
	{
		if (ft_add_or_update_env(cmd->argv[i]) != 0)
			status = 1;
	}
	return (status);
}
