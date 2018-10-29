/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 01:10:52 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/29 01:48:40 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include "../gnl/get_next_line.h"
#include <fcntl.h>

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
	while (get_next_line(fd, &line))
		lines++;
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
		line_nbr++;
	}
	close(fd);
	return (SUCCESS);
}
