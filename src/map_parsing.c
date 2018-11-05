/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 01:10:52 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/11/05 18:03:08 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include <fcntl.h>

int				check_file_extension(char *map_name)
{
	int		len;
	int		i;
	char	*temp;

	len = ft_strlen(map_name);
	i = len;
	temp = ft_strsub(map_name, len - 4, 4);
	if ((ft_strcmp(temp, ".fdf")) != 0)
	{
		free(temp);
		return (INVAL_MAP_ERROR);
	}
	free(temp);
	return (SUCCESS);
}

int				grid_add_line(t_map *map, char *line, int line_nbr)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!line || !(tmp = ft_strsplit(line, ' ')))
		return (INVAL_MEM_ERROR);
	while (*(tmp + i))
		i++;
	if (line_nbr > 0 && i != map->len)
		return (INVAL_MAP_ERROR);
	map->len = i;
	if (!(map->grid[line_nbr] = (int *)ft_memalloc((sizeof(int)) * map->len)))
		return (INVAL_MEM_ERROR);
	i = 0;
	while (*(tmp + i))
	{
		map->grid[line_nbr][i] = ft_atoi(*(tmp + i));
		free(*(tmp + i++));
	}
	free(tmp);
	return (SUCCESS);
}

int				line_count(char *map_name)
{
	int		lines;
	char	*line;
	int		fd;

	lines = 0;
	if ((fd = open(map_name, O_RDONLY)) < 0)
		return (INVAL_MAP_ERROR);
	line = NULL;
	while (get_next_line(fd, &line))
	{
		free(line);
		lines++;
	}
	close(fd);
	return (lines);
}

int				map_parse_to_int(char *map_name, t_map *map)
{
	int		fd;
	int		line_nbr;
	char	*line;

	if ((map->dep = line_count(map_name)) < 0)
		return (INVAL_MAP_ERROR);
	if ((fd = open(map_name, O_RDONLY)) < 0)
		return (INVAL_MAP_ERROR);
	if (!(map->grid = (int **)ft_memalloc(sizeof(int*) * map->dep)))
		return (INVAL_MEM_ERROR);
	line_nbr = 0;
	while (get_next_line(fd, &line))
	{
		if ((grid_add_line(map, line, line_nbr)) < 0)
			return (INVAL_MAP_ERROR);
		free(line);
		line_nbr++;
	}
	close(fd);
	return (SUCCESS);
}
