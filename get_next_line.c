/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 18:18:27 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/20 10:53:07 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	dynamic_malloc(char **old, char *buffer, int bytes_read)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strjoin(*old, buffer, bytes_read, 0);
	if (new == 0)
		return ;
	if (*old)
		free(*old);
	while (buffer[i] && buffer[i] != '\n')
	{
		buffer[i] = 0;
		i++;
	}
	*old = new;
}

void	clean_buffer(char *buffer)
{
	int start;
	int i;

	i = 0;
	start = 0;
	while (start < BUFFER_SIZE && buffer[start] != '\n')
		start++;
	if (buffer[start] == '\n')
		start++;
	while (i < (BUFFER_SIZE - start))
	{
		buffer[i] = buffer[start + i];
		i++;
	}
	while (i < BUFFER_SIZE)
	{
		buffer[i] = 0;
		i++;
	}
}

int		is_newline(char *buffer, char **str, int bytes_read)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			dynamic_malloc(str, buffer, bytes_read);
			if (*str == NULL)
			{
				free(*str);
				return (-1);
			}
			clean_buffer(buffer);
			return (1);
		}
		i++;
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char		*buffer = NULL;
	char			*str;
	int				bytes_read;
	int				result;

	if (fd < 0 || line == NULL)
		return (-1);
	if (buffer == NULL)
		buffer = malloc(BUFFER_SIZE);
	bytes_read = BUFFER_SIZE;
	str = NULL;
	while (bytes_read > 0)
	{
		result = is_newline(buffer, &str, bytes_read);
		if (result != 0)
			return (parse(result, line, &str));
		dynamic_malloc(&str, buffer, bytes_read);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = 0;
	}
	dynamic_malloc(&str, buffer, bytes_read);
	return (parse(bytes_read, line, &str));
}
