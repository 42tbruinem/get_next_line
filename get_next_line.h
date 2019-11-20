/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/20 10:57:00 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/20 10:57:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int		get_next_line(int fd, char **line);
int		parse(int result, char **line, char **str);
char	*ft_strjoin(char *s1, char *s2, int bytes_read, int j);
int		ft_strlen_n(char *str);

#endif
