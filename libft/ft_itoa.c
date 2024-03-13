/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:51:54 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:02:26 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// determines length of number in digits
size_t	ft_numlen(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

// returns the absolute value of a number
int	ft_abs(int n)
{
	if (n < 0)
		return (-1 * n);
	else
		return (n);
}

// puts a number in a string
void	ft_putnbr_str(char *num, int n)
{
	size_t	len;

	if (n == 0)
		num[0] = '0';
	if (n < 0)
		num[0] = '-';
	len = ft_numlen(n);
	while (n != 0)
	{
		num[len - 1] = ft_abs(n % 10) + '0';
		n = n / 10;
		len--;
	}
}

// main control to convert an integer into a string
char	*ft_itoa(int n)
{
	char	*num;

	num = (char *) malloc ((ft_numlen(n) + 1) * sizeof(char));
	if (num == NULL)
		return (NULL);
	num[ft_numlen(n)] = '\0';
	ft_putnbr_str(num, n);
	return (num);
}
