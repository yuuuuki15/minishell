/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:23:25 by mevonuk           #+#    #+#             */
/*   Updated: 2024/01/11 15:55:59 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// zero out buffer
void	zero_buffer(char *buffer)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		buffer[i] = '\0';
		i++;
	}
}

// allocates memory and tacks a character to the end
char	*ft_strexp(char *s1, int c)
{
	char	*new;
	size_t	l1;
	size_t	i;

	if (s1 == NULL)
		l1 = 0;
	else
		l1 = ft_strlen(s1);
	new = (char *) malloc ((l1 + 2) * sizeof(char));
	if (new == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (i < l1)
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(s1);
	return (new);
}

// reads in data from file and assigns to lines based on \n and EOF
char	*ft_get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	static int	b_i;
	static int	b_size;
	char		*line;
	int			read_on;

	line = NULL;
	read_on = 1;
	while (read_on == 1)
	{
		if (b_i >= b_size)
		{
			zero_buffer(buf);
			b_size = read(fd, buf, BUFFER_SIZE);
			b_i = 0;
			if (b_size <= 0)
				return (line);
		}
		if (buf[b_i] == '\n' || (b_size < BUFFER_SIZE && buf[b_i + 1] == '\0'))
			read_on = 0;
		line = ft_strexp(line, buf[b_i++]);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}
/*
int	main(void)
{
	FILE	*file = fopen("example.txt", "r");
	char	*line;
	int	print_on;

	if (file == NULL)
	{
		printf("Failed to open the file.\n");
		return (1);
	}
	printf("Reading lines from the file with buffer size: %d\n", BUFFER_SIZE);
	print_on = 1;
	while (print_on == 1)
	{
		line = get_next_line(fileno(file));
		if (line == NULL)
		{
			free(line);
			print_on = 0;
		}
		else
			printf("line:%s", line);
		free(line);
	}
	fclose(file);
	return (0);
}
*/
