/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 15:16:51 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/29 01:38:22 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static void	get_buff(const int fd, char **buff_p,
	char *(*buff_sp)[MAX_NUM_FILES])
{
	if (!(*buff_sp)[fd])
		(*buff_sp)[fd] = ft_strnew(BUFF_SIZE);
	*buff_p = (*buff_sp)[fd];
}

static int	clean_buff(const int fd, char **buff_p,
	char *(*buff_sp)[MAX_NUM_FILES])
{
	free(*buff_p);
	*buff_p = 0;
	(*buff_sp)[fd] = 0;
	return (0);
}

static int	set_line(char **buff_p, char **line, int *size)
{
	int		i;
	int		j;
	int		nl;

	i = 0;
	while (i < BUFF_SIZE && (*buff_p)[i] != '\0' && (*buff_p)[i] != '\n')
		i++;
	nl = ((*buff_p)[i] == '\n');
	*line = ft_memrealloc(*line, *size + i + 1);
	j = 0;
	while (j < i)
	{
		(*line)[*size + j] = (*buff_p)[j];
		j++;
	}
	*size += i++;
	j = 0;
	while (j + i < BUFF_SIZE && (*buff_p)[j + i] != '\0')
	{
		(*buff_p)[j] = (*buff_p)[j + i];
		j++;
	}
	while (j < BUFF_SIZE && (*buff_p)[j] != '\0')
		(*buff_p)[j++] = '\0';
	return (nl);
}

int			get_next_line(const int fd, char **line)
{
	static char	*buff_storage[MAX_NUM_FILES];
	char		*buff;
	int			size;

	if (fd >= MAX_NUM_FILES || !line || fd < 0)
		return (-1);
	get_buff(fd, &buff, &buff_storage);
	if (read(fd, buff, 0) == -1)
		return (clean_buff(fd, &buff, &buff_storage) - 1);
	if (!(*line = ft_memalloc(1)))
		return (-1);
	size = 0;
	while (42)
		if (set_line(&buff, line, &size))
			return (1);
		else if (read(fd, buff, BUFF_SIZE) == 0)
		{
			if (size == 0)
				free(*line);
			return ((size == 0) ? clean_buff(fd, &buff, &buff_storage) : 1);
		}
}
