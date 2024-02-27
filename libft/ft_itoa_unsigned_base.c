/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:51:54 by mevonuk           #+#    #+#             */
/*   Updated: 2023/12/14 13:14:10 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// determines length of number in digits given base
int	numlen(unsigned long long n, int base)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

// puts a number in a string
void	putnbr_str_b(char *num, unsigned long long n, char *s, int base)
{
	size_t	len;

	if (n == 0)
		num[0] = s[0];
	len = numlen(n, base);
	while (n != 0)
	{
		num[len - 1] = s[n % base];
		n = n / base;
		len--;
	}
}

// makes bases ten and hex (16) uppercase and lowercase
void	make_base(char *s, int format)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		s[i] = i + '0';
		i++;
	}
	while (i < 16)
	{
		if (format == 'x' || format == 'p')
			s[i] = 'a' + i - 10;
		if (format == 'X')
			s[i] = 'A' + i - 10;
		if (format == 'u' || format == 'i' || format == 'd')
			s[i] = '\0';
		i++;
	}
	s[i] = '\0';
}

// main control to convert an integer into a string given base
int	ft_itoa_unsigned_base(unsigned long long n, int format)
{
	char	*num;
	char	s[16];
	int		base;

	base = 16;
	if (format == 'u' || format == 'i' || format == 'd')
		base = 10;
	make_base(s, format);
	num = (char *) malloc ((numlen(n, base) + 1) * sizeof(char));
	if (num == NULL)
		return (-1);
	num[numlen(n, base)] = '\0';
	putnbr_str_b(num, n, s, base);
	ft_putstr(num);
	free(num);
	return (numlen(n, base));
}
