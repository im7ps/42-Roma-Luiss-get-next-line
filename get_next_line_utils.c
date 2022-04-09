/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:39:22 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/09 18:39:59 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len1;
	size_t		len2;
	size_t		i;
	char		*stack;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	stack = (char *) malloc(sizeof(char) * (len1 + len2 + 1));
	if (!stack)
		return (NULL);
	while (*s1 != '\0')
		stack[i++] = *s1++;
	while (*s2 != '\0')
		stack[i++] = *s2++;
	stack[i] = '\0';
	return (stack);
}
