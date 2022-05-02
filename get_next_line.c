/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:12:41 by sgerace           #+#    #+#             */
/*   Updated: 2022/05/02 21:46:36 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*update_line(char *save)
{
	int		i;
	int		j;
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
	j = 0;
	while (save[i])
		s[j++] = save[i++];
	s[j] = '\0';
	free(save);
	return (s);
}

char	*get_line(char	*dst)
{
	char	*temp;
	int		i;

	i = 0;
	if (!dst[i])										//con un empty file il controllo nel main lo skippa mentre entra in questo if, ritornando subito null, perche non viene skippato anche questo? (forse nel main controllo se il puntatore punta a qualcosa in generale, qui proprio il primo elemento deve essere diverso da '\0')
		return (NULL);
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
		temp[i++] = '\n';
	temp[i] = '\0';
	// printf("Temp:\n%s", temp);
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
		if (char_num == -1)
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

char	*get_next_line(int fd)
{
	static char	*dst;
	char		*the_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	dst = read_save(fd, dst);
	if (!dst)                         //se non ci fosse questo controllo con un fd invalid andrebbe in SIGSEGV, perche?
		return (NULL);
	the_line = get_line(dst);
	dst = update_line(dst);
	return (the_line);
}

// int	main(void)
// {
// 	int		fd;
// 	int		i;

// 	i = 0;
// 	fd = open("test.txt", O_RDONLY);
// 	while (i++ < 7)
// 	{
// 		printf("Result: %s", get_next_line(fd));
// 	}
// 	return (0);
// }
