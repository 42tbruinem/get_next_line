/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/09 22:38:51 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/09 22:38:51 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		ft_strlen_n(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void	clean_buffer(char *buffer, int bytes_read)
{
	int i;

	i = 0;
	while (i < bytes_read && buffer[i] != '\n')
	{
		buffer[i] = 0;
		i++;
	}
}

char	*ft_realloc(char *str, char *buffer, int bytes_read)
{
	char	*new;
	int		i;

	i = 0;
	if (bytes_read == -1)
		return (NULL);
	if (bytes_read > ft_strlen_n(buffer))
		bytes_read = ft_strlen_n(buffer);
	new = malloc(sizeof(char) * (ft_strlen_n(str) + bytes_read + 1));
	if (str)
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	while (i < (ft_strlen_n(str) + bytes_read))
	{
		new[i] = *buffer;
		buffer++;
		i++;
	}
	new[i] = 0;
	free(str);
	clean_buffer(buffer, bytes_read);
	return (new);
}

void	move_buffer(char *buffer, int bytes_read)
{
	int start;
	int i;

	i = 0;
	start = 0;
	while (start < bytes_read && buffer[start] != '\n')
		start++;
	if (buffer[start] == '\n')
		start++;
	while (i < (bytes_read - start))
	{
		buffer[i] = buffer[start + i];
		i++;
	}
	while (i < bytes_read)
	{
		buffer[i] = 0;
		i++;
	}
}

int		is_newline(char *buffer, char **line, int bytes_read)
{
	int i;

	i = 0;
	while (buffer[i] && i < bytes_read)
	{
		if (buffer[i] == '\n')
		{
			*line = ft_realloc(*line, buffer, bytes_read);
			if (line == NULL)
				return (-1);
			move_buffer(buffer, bytes_read);
			return (1);
		}
		i++;
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char		buffer[BUFFER_SIZE];
	static int		cur_fd = 0;
	int				bytes_read;
	int				result;

	bytes_read = BUFFER_SIZE;
	if (fd != cur_fd)
		clean_buffer(buffer, bytes_read);
	cur_fd = fd;
	*line = NULL;
	while (bytes_read > 0)
	{
		result = is_newline(buffer, line, bytes_read);
		if (result != 0)
			return (result);
		*line = ft_realloc(*line, buffer, bytes_read);
		bytes_read = read(fd, &buffer[0], BUFFER_SIZE);
	}
	*line = ft_realloc(*line, buffer, bytes_read);
	return (bytes_read);
}
