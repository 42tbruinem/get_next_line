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
//	printf("buffer: %s\n", buffer);
	while (i < (ft_strlen_n(str) + bytes_read))
	{
		new[i] = *buffer;
		buffer++;
		i++;
	}
	new[i] = 0;
	free(str);
//	printf("string: %s\n", new);
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
//	printf("clean buffer: %s\n", buffer);
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

t_store	*item_new(int fd)
{
	t_store *item;

	item = (t_store *)malloc(sizeof(t_store));
	if (!item)
		return (NULL);
	item->fd = fd;
	item->buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!item->buffer)
		return (NULL);
	item->next = NULL;
	clean_buffer(item->buffer, BUFFER_SIZE + 1);
	return (item);
}

t_store	*get_store(t_store **fd_store, int fd)
{
	t_store *list;
	t_store *last;

	list = *fd_store;
	last = *fd_store;
	if (!list)
	{
		*fd_store = item_new(fd);
		return (*fd_store);
	}
	while (list)
	{
		last = list;
		if (list->fd == fd)
		{
//			list->buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
//			printf("bufferino: %s\n", list->buffer);
			return (list);
		}
		list = list->next;
	}
	last->next = item_new(fd);
	return (last->next);
}

void	ft_lstclear(t_store **lst, void (*del)(char *, int))
{
	t_store	*last;
	t_store	**begin;

	if (lst == NULL || *lst == NULL)
		return ;
	begin = lst;
	while (*lst)
	{
		last = *lst;
		*lst = (*lst)->next;
		del(last->buffer, BUFFER_SIZE);
		free(last->buffer);
		free(last);
		last = NULL;
	}
	*begin = NULL;
}

int		memory_leak_prevention_squad(char **line, t_store *store, t_store *current, int result)
{
	t_store *temp;

	temp = store;
	if (result == -1)
	{
		ft_lstclear(&store, &clean_buffer);
		*line = NULL;
		return (result);
	}
//	free(current->buffer);
	if (result == 0)
	{
		while (temp && temp != current)
		{
			store = temp;
			temp = temp->next;
		}
		store->next = current->next;
		clean_buffer(current->buffer, BUFFER_SIZE);
		free(current);
	}
	return (result);
}

int		get_next_line(int fd, char **line)
{
	static t_store		*fd_store = NULL;
	t_store				*current;
	int					bytes_read;
	int					result;

	bytes_read = BUFFER_SIZE;
	current = get_store(&fd_store, fd);
	*line = NULL;
	while (bytes_read > 0)
	{
		result = is_newline(current->buffer, line, bytes_read);
		if (result != 0)
			return (result);
		*line = ft_realloc(*line, current->buffer, bytes_read);
		bytes_read = read(fd, current->buffer, BUFFER_SIZE);
	}
	*line = ft_realloc(*line, current->buffer, bytes_read);
	return (bytes_read);
}
