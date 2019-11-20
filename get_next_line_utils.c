/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 13:11:34 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/20 10:51:35 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen_n(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int		parse(int result, char **line, char **str)
{
	if (result == 0 || result == 1)
		*line = *str;
	else
		free(*str);
	return (result);
}

char	*ft_strjoin(char *s1, char *s2, int bytes_read, int j)
{
	int		s1len;
	char	*new;
	int		i;

	s1len = 0;
	i = 0;
	if (s1)
		s1len = ft_strlen_n(s1);
	if (bytes_read > ft_strlen_n(s2))
		bytes_read = ft_strlen_n(s2);
	new = (char *)malloc(sizeof(char) * (s1len + bytes_read + 1));
	if (s1)
		while (s1[i])
		{
			new[i] = s1[i];
			i++;
		}
	while (s2[j] && j < bytes_read)
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = 0;
	return (new);
}
