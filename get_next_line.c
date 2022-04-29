/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:12:41 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/29 15:47:53 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_line(char	*save)
{
	char	*temp;
	int		i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	temp = (char *) malloc (sizeof(char) * (i + 2));
	temp[i + 2] = '\0';
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		temp[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		temp[i] = '\n';
	printf("Save: %s\n", save);
	printf("Temp: %s\n", temp);
	return (temp);
}

char	*read_save(int fd, char	*save)
{
	int		char_num;
	char	*buffer;

	buffer = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE + 1] = '\0';
	char_num = 1;
	while (!ft_strchr(save, '\n') && char_num != 0)
	{
		char_num = read(fd, buffer, BUFFER_SIZE);
		if (char_num == 0 && char_num == -1)
		{
			free(buffer);
			return (NULL);
		}
		save = ft_strjoin(save, buffer);
		printf("Save: %s\n", save);
	}
	free (buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*the_line;

	if (BUFFER_SIZE <= 0 && fd < 0)
		return (NULL);
	save = read_save(fd, save);
	the_line = get_line(save);
	return (save);
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
