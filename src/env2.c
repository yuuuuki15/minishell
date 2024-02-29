/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:40:31 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/29 14:44:56 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_show_env(void)
{
	t_env	*curr;

	if (shell.env == NULL)
		return ;
	curr = shell.env;
	while (curr != NULL)
	{
		ft_printf("%s", curr->key);
		ft_printf("%s\n", curr->value);
		curr = curr->next;
	}
}
