/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 13:18:47 by jolopez-          #+#    #+#             */
/*   Updated: 2022/05/17 18:33:10 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_new_container(char *container)
{
	int		i;
	int		j;
	char	*sol;

	i = 0;
	while (container[i] && container[i] != '\n')
		i++;
	if (container[i] == '\0')
	{
		free (container);
		return (NULL);
	}
	sol = malloc(sizeof(char) * (ft_str_len(container) - i + 1));
	if (!sol)
		return (NULL);
	i++;
	j = 0;
	while (container[i])
		sol[j++] = container[i++];
	sol[j] = '\0';
	free(container);
	return (sol);
}

char	*ft_get_line(char *container)
{
	size_t		i;
	char	*sol;

	i = 0;
	if (!container[i])
		return (NULL);
	while (container[i] && container[i] != '\n')
		i++;
	sol = malloc(sizeof(char) * (i + 2));
	if (!sol)
		return (NULL);
	i = 0;
	while (container[i] && container[i] != '\n')
	{
		sol[i] = container[i];
		i++;
	}
	if (container[i] == '\n')
	{
		sol[i] = container[i];
		i++;
	}
	sol[i] = '\0';
	return (sol);
}

char	*ft_read_buffer(int fd, char *container)
{
	char	*buffer;
	int		buffer_len;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer_len = 1;
	while (!ft_str_find_chr(container, '\n') && buffer_len != 0)
	{
		buffer_len = read(fd, buffer, BUFFER_SIZE);
		if (buffer_len == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[buffer_len] = '\0';
		container = ft_str_join_buffer(container, buffer);
	}
	free (buffer);
	return (container);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*container[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	container[fd] = ft_read_buffer(fd, container[fd]);
	if (!container[fd])
		return (NULL);
	line = ft_get_line(container[fd]);
	container[fd] = ft_new_container(container[fd]);
	return (line);
}
