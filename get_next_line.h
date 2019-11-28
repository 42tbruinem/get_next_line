/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/09 23:16:26 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/28 22:53:18 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_store
{
	int				fd;
	char			*buffer;
	struct s_store	*next;
}					t_store;

int		get_next_line(int fd, char **line);
void	put_mem(char *str, size_t len);
int		ft_strlen_n(char *str);
void	clean_buffer(char *buffer, int bytes_read, int full);
t_store	*item_new(int fd);
void	move_buffer(char *buffer, int bytes_read);
char	*ft_realloc(char *str, char *buffer, int bytes_read, int j);

#endif
