/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 09:58:29 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/25 09:58:43 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sorts environment lst by alphabet
static t_env	**sort_env_list(t_env **env_list, int count)
{
	int		i;
	int		swapped;
	t_env	*temp;

	if (count <= 1)
		return (env_list);
	swapped = 0;
	i = 0;
	while (i < count - 1)
	{
		if (ft_strcmp(env_list[i]->key, env_list[i + 1]->key) > 0)
		{
			temp = env_list[i];
			env_list[i] = env_list[i + 1];
			env_list[i + 1] = temp;
			swapped = 1;
		}
		i++;
	}
	if (swapped)
		return (sort_env_list(env_list, count - 1));
	return (env_list);
}

// duplicates env into table for sorting
static t_env	**duplicate_env(int count, t_shell *shell)
{
	t_env	*curr;
	t_env	**sorted_env;
	int		i;

	sorted_env = (t_env **)malloc(sizeof(t_env *) * count);
	if (!sorted_env)
		ft_error(ERR_MALLOC);
	curr = shell->env;
	i = 0;
	while (curr)
	{
		sorted_env[i] = curr;
		curr = curr->next;
		i++;
	}
	return (sorted_env);
}

// prints env var to screen in export format, alphabetical order
void	ft_show_export(t_shell *shell)
{
	t_env	*curr;
	t_env	**sorted_env;
	int		count;
	int		i;

	i = 0;
	curr = shell->env;
	count = 0;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	sorted_env = duplicate_env(count, shell);
	if (!sorted_env)
		ft_error(ERR_MALLOC);
	sorted_env = sort_env_list(sorted_env, count);
	while (i < count)
	{
		ft_printf("export %s=%s\n", sorted_env[i]->key, sorted_env[i]->value);
		i++;
	}
	free(sorted_env);
}
