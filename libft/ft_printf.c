/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:46:51 by mevonuk           #+#    #+#             */
/*   Updated: 2023/12/14 13:13:48 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// outputs pointer to screen and returns length
int	output_pointer(va_list args)
{
	unsigned long long	ul;
	int					count;

	count = 0;
	ul = va_arg(args, unsigned long long);
	if (ul != 0)
	{
		count += ft_putstr("0x");
		count += ft_itoa_unsigned_base(ul, 'p');
	}
	else
		count += ft_putstr("(nil)");
	return (count);
}

// outputs number to screen and returns length
int	output_number(va_list args, const char format)
{
	unsigned int	uc;
	int				count;
	long int		c;

	count = 0;
	if (format == 'd' || format == 'i')
	{
		c = va_arg(args, int);
		if (c < 0)
		{
			count += ft_putchar('-');
			c = -c;
		}
		return (count + ft_itoa_unsigned_base(c, format));
	}
	if (format == 'x' || format == 'X' || format == 'u')
	{
		uc = va_arg(args, unsigned int);
		count += ft_itoa_unsigned_base(uc, format);
	}
	return (count);
}

// outputs a string or char to the screen and returns length
int	output_string(va_list args, const char format)
{
	int		c;
	char	*str;

	if (format == 'c')
	{
		c = va_arg(args, int);
		return (ft_putchar(c));
	}
	if (format == 's')
	{
		str = va_arg(args, char *);
		if (str != NULL)
			return (ft_putstr(str));
		else
			return (ft_putstr("(null)"));
	}
	return (0);
}

// checks for formatting request, otherwise just prints, returns print length
int	check_list(va_list args, const char *list)
{
	int	count;

	count = 0;
	while (*list != '\0')
	{
		if (*list == '%')
		{
			list++;
			if (*list == 'c' || *list == 's')
				count += output_string(args, *list);
			else if (*list == 'i' || *list == 'd')
				count += output_number(args, *list);
			else if (*list == 'u' || *list == 'X' || *list == 'x')
				count += output_number(args, *list);
			else if (*list == 'p')
				count += output_pointer(args);
			else if (*list == '%')
				count += ft_putchar('%');
		}
		else
			count += ft_putchar(*list);
		++list;
	}
	return (count);
}

// variadic function to read in arguments for printing
int	ft_printf(const char *list, ...)
{
	int		count;
	va_list	args;

	va_start(args, list);
	count = 0;
	if (list == NULL)
		return (-1);
	count = check_list(args, list);
	va_end(args);
	return (count);
}
/*
int	main(void)
{
	char	c;
	int	num_bytes;
	char	s[] = "hello";
	int	d;

	c = 'b';
	d = -3456;
	//s = NULL;
	printf("%%a %c %s %p %i %u %X\n", c, s, s, d, d, d);
	num_bytes = ft_printf("%%a %c %s %p %i %u %X\n", c, s, s, d, d, d);
	printf("num of bytes printed: %d\n", num_bytes);
	printf("O:%d\n", printf("%p", s));
	ft_printf("n:%d\n", ft_printf("%p", s));
	ft_printf(0);
	return (0);
}
*/
