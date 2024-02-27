/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:38:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/27 17:54:54 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param char* name
 * @return t_env env
 *
 * Take a key string and return environment pointer.
 * return NULL if there's no environment.
*/
t_env	*ft_get_env(char *name)
{
	int	i;
	t_env	*curr;

	curr = shell.env;
	while (curr)
	{
		if (ft_strcmp(curr->key, name) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/**
 * take key and value, then register to environment
*/
void	ft_add_env(char *key, char *value)
{
	t_env	*env;

	if (get_env())
}
