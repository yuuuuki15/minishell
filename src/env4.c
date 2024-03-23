/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:36:35 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/23 09:45:50 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_shlvl(t_shell *shell)
{
	t_env	*env_var;
	char	*new_value;
	int		shlvl;

	env_var = shell->env;
	while (env_var != NULL)
	{
		if (ft_strcmp(env_var->key, "SHLVL") == 0)
		{
			shlvl = ft_atoi(env_var->value);
			new_value = ft_itoa(shlvl + 1);
			if (new_value == NULL)
				ft_error(ERR_MALLOC);
			free(env_var->value);
			env_var->value = new_value;
			return;
		}
		env_var = env_var->next;
	}
	ft_add_env(ft_strdup("SHLVL"), ft_strdup("1"), shell);
}
