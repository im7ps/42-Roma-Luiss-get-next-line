/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:12:41 by sgerace           #+#    #+#             */
/*   Updated: 2022/05/04 16:09:02 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_line(char *current_line)
{
	int		i;
	int		j;
	char	*extra_char_array;

	i = 0;
	while (current_line[i] && current_line[i] != '\n')
		i++;
	if (!current_line[i])
	{
		free(current_line);
		return (NULL);
	}
	extra_char_array = (char *)malloc(sizeof(char) * (ft_strlen(current_line) - i + 1));
	//printf("Avanzano questi char: %s", extra_char_array);
	if (!extra_char_array)
		return (NULL);
	i++;
	j = 0;
	while (current_line[i])
		extra_char_array[j++] = current_line[i++];
	extra_char_array[j] = '\0';
	free(current_line);
	return (extra_char_array);
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
	if (!dst)
		return (NULL);
	the_line = get_line(dst);
	dst = update_line(dst);
	return (the_line);
}
