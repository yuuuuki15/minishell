/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:42:14 by mevonuk           #+#    #+#             */
/*   Updated: 2024/01/11 17:02:32 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_decimal(char c)
{
	if (c == '.')
		return (1);
	return (0);
}

float	get_decimals(const char *nptr, float nb, int i)
{
	int	k;

	i++;
	k = 10;
	while (ft_isdigit(nptr[i]))
	{
		nb = nb + (nptr[i] - '0') / (float)(k);
		i++;
		k = k * 10;
	}
	return (nb);
}

// converts string to float
float	ft_atof(const char *nptr)
{
	int		i;
	int		sign;
	float	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	if (is_decimal(nptr[i]))
		nb = get_decimals(nptr, nb, i);
	return (sign * nb);
}
