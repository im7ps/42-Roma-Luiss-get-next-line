/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:12:41 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/29 18:23:40 by sgerace          ###   ########.fr       */
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
	if (!temp)
		return (NULL);
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
	}
	free(buffer);
	return (dst);
}

char	*ft_save(char *save)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!s)
		return (NULL);
	i++;
	c = 0;
	while (save[i])
		s[c++] = save[i++];
	s[c] = '\0';
	free(save);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*dst;
	char		*the_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	dst = read_save(fd, dst);
	if (!dst)
		return (NULL);
	the_line = get_line(dst);
	dst = ft_save(dst);
	return (the_line);
}

int	main(void)
{
	int		fd;
	int		i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i++ < 5)
	{
		printf("Result: %s\n", get_next_line(fd));
	}
	return (0);
}
