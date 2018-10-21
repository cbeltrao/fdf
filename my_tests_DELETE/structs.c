/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:43:40 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/21 22:24:04 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>

int	struct_tests(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	map->length = 10;
	map->depth = 15;
	map->coord_grid = (t_2dpoint **)malloc(sizeof(t_2dpoint *) * map->depth);
	while(i < map->depth)
	{
		map->coord_grid[i] = (t_2dpoint *)malloc(sizeof(t_2dpoint) * map->length);
		j = 0;
		while(j < map->length)
		{
			map->coord_grid[i][j].x = j;
			map->coord_grid[i][j].y = j * i;
			j++;
		}
		i++;
	}
	return (0);
}

int	map_init(void)
{
	t_map *map;
	int	i;
	int	j;

	map = (t_map *)malloc(sizeof(t_map));
	struct_tests(map);
	i = 0;
	j = 0;
	while (i < map->depth)
	{
		j = 0;
		while( j < map->length)
		{
			printf("map->coord_grid[%d][%d]->x = %d, map->coord_grid[%d][%d]->y = %d\n",
					i, j, map->coord_grid[i][j].x, i, j, map->coord_grid[i][j].y);
			j++;
		}
		printf("endofline\n");
		i++;
	}
	return (0);
}

int	main(void)
{
	map_init();
	return (0);
}
