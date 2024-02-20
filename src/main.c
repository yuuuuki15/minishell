/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/20 18:20:29 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;

	(void)ac;
	(void)av;
	while (1)
	{
		ft_printf("minishell %% ");
		str = ft_get_next_line(STDIN_FILENO);
		if (ft_strcmp(str, "exit\n") == 0)
			exit (0);
		ft_printf("given command: %s\n", str);
	}
	return (0);
}
