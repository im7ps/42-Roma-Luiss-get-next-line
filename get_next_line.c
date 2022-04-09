/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:12:41 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/09 18:48:23 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	size_t		current_line_char_num;
	static char	*final_string;
	size_t		i;

	if (fd < 0)
		return (NULL);
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	current_line_char_num = read(fd, buffer, BUFFER_SIZE);
	if (current_line_char_num == 0 || current_line_char_num == -1)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE)
	{
		final_string = ft_strjoin(final_string, buffer);
		free(buffer);
		return (get_next_line(fd));
	}
	return (final_string);
}
