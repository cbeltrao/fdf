/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:54:03 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/27 16:27:00 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include "mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gnl/get_next_line.h"
#include "libft/includes/libft.h"
#include <unistd.h>
#define DEPTH_OF(x) (sizeof(x)/sizeof(x[0])

int		image_refresh(t_mlx *mlx, char *mode);

int			deal_key(int key, t_mlx *mlx)
{
	ft_putchar(key);
	printf("ENTROU%dSAIU\n", key);
	fflush(stdout);
	if(key == 12)
		image_refresh(mlx, "plus_scale");
	else if(key == 13)
		image_refresh(mlx, "minus_scale");
	else if(key == 14)
		image_refresh(mlx, "plus_z_height");
	else if (key == 15)
		image_refresh(mlx, "minus_z_height");
	else if (key == 0)
		image_refresh(mlx, "add_move_x");
	else if (key == 1)
		image_refresh(mlx, "sub_move_x");
	else if (key == 2)
		image_refresh(mlx, "add_move_y");
	else if (key == 3)
		image_refresh(mlx, "sub_move_y");
	else if (key == 53)
	{
		printf("ESC PRESSED\n");
		fflush(stdout);
		return (1);
	}
	return (0);
}

void		iso(int *x, int *y, int z)
{
	int	previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

t_2dpoint	set_point(int x, int y, int z)
{
	t_2dpoint temp;

	temp.x = x;
	temp.y = y;
	temp.z = z;
	return (temp);
}

void		ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		fill_pixel(unsigned int *img, int x, int y, int z)
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

void		draw_line_da_y(t_mlx *mlx, t_2dpoint p1, t_2dpoint p2)
{
	int x;
	int y;
	int dx;
	int dy;
	int xincr;
	int	yincr;
	int err;
	int i;

	dx = abs(p2.x - p1.x);
	dy = abs(p1.y - p2.y);
	i = 0;
	xincr = (p1.x < p2.x ? 1 : -1);
	yincr = (p1.y < p2.y ? 1 : -1);
	x = p1.x;
	y = p1.y;
	err = dy / 2;
	while (i++ < dy)
	{
		y += yincr;
		err += dx;
		if (err > dy)
		{
			err -= dy;
			x += xincr;
		}
		fill_pixel(mlx->img.img_ui, x, y, p1.z);
	}
	fill_pixel(mlx->img.img_ui, x, y, p1.z);
}

void		draw_line_da_x(t_mlx *mlx, t_2dpoint p1, t_2dpoint p2)
{
	int x;
	int y;
	int dx;
	int dy;
	int xincr;
	int yincr;
	int err;
	int i;

	dx = abs(p2.x - p1.x);
	dy = abs(p2.y - p1.y);
	i = 0;
	xincr = (p1.x < p2.x ? 1 : -1);
	yincr = (p1.y < p2.y ? 1 : -1);
	x = p1.x;
	y = p1.y;
	err = dx / 2;
	while (i < dx)
	{
		x += xincr;
		err += dy;
		if (err > dx)
		{
			err -= dx;
			y += yincr;
		}
		fill_pixel(mlx->img.img_ui, x, y, p1.z);
		i++;
	}
	fill_pixel(mlx->img.img_ui, p1.x, p1.y, p1.z);
	fill_pixel(mlx->img.img_ui, p2.x, p2.y, p2.z);
}

int			draw_line(t_mlx *mlx, t_2dpoint p1, t_2dpoint p2)
{
	int dx;
	int dy;
	int dominant_axis;

	dx = abs(p2.x - p1.x);
	dy = abs(p2.y - p1.y);
	dominant_axis = (dx > dy ? 'x' : 'y');
	if (dominant_axis == 'x')
		draw_line_da_x(mlx, p1, p2);
	else
		draw_line_da_y(mlx, p1, p2);
	return (0);
}

int			set_p_and_draw(t_mlx *mlx, t_map *map, int i, int j)
{
	if (j == 0)
	{
		map->p[i][j] = set_point((900) - map->grid[i][j]
				+ map->move_x,
				(0) - map->grid[i][j]
			   	+ (map->k * i) + map->move_y,
				(map->grid[i][j]) * map->z_h);
		iso(&map->p[i][j].x, &map->p[i][j].y, map->p[i][j].z);
	}
	else if (j > 0)
	{
		map->p[i][j] = set_point((900 - map->grid[i][0]) - map->grid[i][j]
				+ (map->k * j) + map->move_x,
				((0) - map->grid[i][0]) - map->grid[i][j]
			   	+ (map->k * i) + map->move_y,
				(map->grid[i][j]) * map->z_h);
		iso(&map->p[i][j].x, &map->p[i][j].y, map->p[i][j].z);
		draw_line(mlx, map->p[i][j - 1], map->p[i][j]);
	}
	if (i != 0)
		draw_line(mlx, map->p[i - 1][j], map->p[i][j]);
	return (0);
}

int			grid_setup(t_mlx *mlx, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->dep)
	{
		if (!(map->p[i] = (t_2dpoint *)malloc(sizeof(t_2dpoint) * map->len)))
			return (INVAL_MEM_ERROR);
		j = 0;
		while (j < map->len)
		{
			set_p_and_draw(mlx, map, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

int			grid_add_line(t_map *map, char *line, int line_nbr)
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
	if (!(map->grid[line_nbr] = (int *)malloc((sizeof(int)) * map->len)))
		return (INVAL_MEM_ERROR);
	i = 0;
	while (*(tmp + i))
	{
		map->grid[line_nbr][i] = ft_atoi(*(tmp + i));
		free(*(tmp + i++));
	}
	free(tmp);
	return (0);
}

int			line_count(char *map_name)
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

int			read_map(char *map_name, t_map *map)
{
	int		fd;
	int		line_nbr;
	char	*line;

	if ((line_nbr = line_count(map_name)) < 0)
		return (INVAL_MAP_ERROR);
	if ((fd = open(map_name, O_RDONLY)) < 0)
		return (INVAL_MAP_ERROR);
	map->dep = line_nbr;
	if (!(map->grid = (int **)malloc(sizeof(int*) * line_nbr)))
		return (INVAL_MEM_ERROR);
	line_nbr = 0;
	while (get_next_line(fd, &line))
	{
		if ((grid_add_line(map, line, line_nbr)) < 0)
			return (INVAL_MAP_ERROR);
		line_nbr++;
	}
	close(fd);
	return (0);
}

int			set_map(t_mlx *mlx, char *map_name)
{
	t_map	*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))) || !map_name || !(*map_name))
		return (INVAL_MEM_ERROR);
	map->k = SCALE(2); // distancia entre pontos e altura do z
	map->z_h = 1;
	map->move_x = 0;
	map->move_y = 0;
	if (read_map(map_name, map) < 0)
		return (INVAL_MAP_ERROR);
	mlx->map = map;
	if (!(map->p = (t_2dpoint **)malloc(sizeof(t_2dpoint *) * map->dep)))
		return (INVAL_MEM_ERROR);
	if (grid_setup(mlx, map) < 0)
		return (INVAL_MEM_ERROR);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (0);
}

int		image_refresh(t_mlx *mlx, char *mode)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	if(!ft_strcmp(mode, "plus_scale"))
		mlx->map->k += 1;
	else if (!ft_strcmp(mode, "minus_scale"))
		mlx->map->k -= (mlx->map->k == 1 ? 0 : 1);
	else if (!ft_strcmp(mode, "plus_z_height"))
		mlx->map->z_h += 1;
	else if (!ft_strcmp(mode, "minus_z_height"))
		mlx->map->z_h -= 1;
	else if (!ft_strcmp(mode, "add_move_x"))
		mlx->map->move_x += 10;
	else if (!ft_strcmp(mode, "sub_move_x"))
		mlx->map->move_x -= 10;
	else if (!ft_strcmp(mode, "add_move_y"))
		mlx->map->move_y += 10;
	else if (!ft_strcmp(mode, "sub_move_y"))
		mlx->map->move_y -= 10;
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->img.img_ui = (unsigned int *)mlx_get_data_addr(mlx->img.img_ptr,
			&(mlx->img.size_l), &(mlx->img.bpp), &(mlx->img.endian));
	if (grid_setup(mlx, mlx->map) < 0)
		return (INVAL_MEM_ERROR);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (0);
}

int			fdf_start(char *map_name)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx))))
		return (INVAL_MEM_ERROR);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Fdf");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->img.img_ui = (unsigned int *)mlx_get_data_addr(mlx->img.img_ptr
			, &(mlx->img.size_l), &(mlx->img.bpp), &(mlx->img.endian));
	if (set_map(mlx, map_name) < 0)
		return (INVAL_MAP_ERROR);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
			400, 300, 0XFF00FF, "Belo chupa orla");
	mlx_key_hook(mlx->win_ptr, deal_key, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (1);
}

int			main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("Usage ./fdf <file>\n");
		return (-1);
	}
	if (fdf_start(argv[1]) < 0)
		return (-1);
	return (0);
}
