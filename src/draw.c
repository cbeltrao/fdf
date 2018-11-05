/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 01:01:30 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/11/05 18:02:52 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include <math.h>

t_point			set_point(int x, int y, int z)
{
	t_point temp;

	temp.x = x;
	temp.y = y;
	temp.z = z;
	temp.iso_x = (x - y) * cos(0.523599);
	temp.iso_y = -z + (x + y) * sin(0.523599);
	return (temp);
}

void			fill_pixel(unsigned int *img, int x, int y, int z)
{
	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
	{
		if (z < 0)
			img[y * WIDTH + x] = 0xff00ff;
		else if (z == 0)
			img[y * WIDTH + x] = 0xffffff;
		else if (z <= 10)
			img[y * WIDTH + x] = 0xffffdd;
		else if (z <= 20)
			img[y * WIDTH + x] = 0xffff51;
		else if (z <= 25)
			img[y * WIDTH + x] = 0xffff15;
		else if (z <= 50)
			img[y * WIDTH + x] = 0xff7d23;
		else if (z <= 100)
			img[y * WIDTH + x] = 0xff0051;
		else
			img[y * WIDTH + x] = 0xff140d;
	}
}

int				set_coords_and_draw(t_mlx *mlx, t_map *map, int i, int j)
{
	int x;
	int y;
	int z;

	z = map->grid[i][j] * map->height_k;
	x = (INITIAL_X_POS) + (map->k * (j)) - z + map->move_x;
	y = (INITIAL_Y_POS) + (map->k * (i)) - z + map->move_y;
	map->p[i][j] = set_point(x, y, z);
	if (j != 0)
		bresenham_draw_line(mlx, map->p[i][j - 1], map->p[i][j], map->cam);
	if (i != 0)
		bresenham_draw_line(mlx, map->p[i - 1][j], map->p[i][j], map->cam);
	return (SUCCESS);
}

int				set_points_and_draw(t_mlx *mlx, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->dep)
	{
		if (map->p[i])
			free(map->p[i]);
		if (!(map->p[i] = (t_point *)ft_memalloc(sizeof(t_point) * map->len)))
			return (INVAL_MEM_ERROR);
		j = 0;
		while (j < map->len)
		{
			set_coords_and_draw(mlx, map, i, j);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
