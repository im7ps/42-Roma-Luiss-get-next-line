/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:12:41 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/29 16:18:05 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_line(char	*dst)
{
	char	*temp;
	int		i;

	i = 0;
	while (dst[i] && dst[i] != '\n')
		i++;
	temp = (char *) malloc (sizeof(char) * (i + 2));
	temp[i + 2] = '\0';
	i = 0;
	while (dst[i] && dst[i] != '\n')
	{
		temp[i] = dst[i];
		i++;
	}
	if (dst[i] == '\n')
		temp[i] = '\n';
	printf("Temp:\n%s", temp);
	return (temp);
}

char	*read_save(int fd, char	*dst)
{
	int		char_num;
	char	*buffer;

	buffer = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE + 1] = '\0';
	char_num = 1;
	while (!ft_strchr(dst, '\n') && char_num != 0)
	{
		char_num = read(fd, buffer, BUFFER_SIZE);
		if (char_num == 0 && char_num == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[char_num] = '\0';
		dst = ft_strjoin(dst, buffer);
		printf("dst:\n%s", dst);
	}
	free (buffer);
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	*dst;
	char		*the_line;

	if (BUFFER_SIZE <= 0 && fd < 0)
		return (NULL);
	dst = read_save(fd, dst);
	the_line = get_line(dst);
	return (dst);
}

int	main	(void)
{
	int		fd;
	int		i = 0;

	fd = open("test.txt", O_RDONLY);
	while (i++ < 1)
	{
		get_next_line(fd);
		// printf("Line %i: %s\n", i, );
	}
	return (0);
}
