/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 22:59:53 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/28 22:19:33 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				fdf_refresh(t_mlx *mlx, int mode);

int				deal_key_sub(int key, t_mlx *mlx)
{
	if (key == X)
		fdf_refresh(mlx, PARALLEL);
	else if (key == I)
		fdf_refresh(mlx, ANGLE_INCREASE);
	else if (key == O)
		fdf_refresh(mlx, ANGLE_DECREASE);
	else if (key == ESC)
		fdf_refresh(mlx, EXIT);
	else if (key == T)
		fdf_refresh(mlx, MAP_RESET);
	return (SUCCESS);
}

int				deal_key(int key, t_mlx *mlx)
{
	if (key == E)
		fdf_refresh(mlx, ZOOM_IN);
	else if (key == Q)
		fdf_refresh(mlx, ZOOM_OUT);
	else if (key == R)
		fdf_refresh(mlx, INCREASE_HEIGHT);
	else if (key == F)
		fdf_refresh(mlx, DECREASE_HEIGHT);
	else if (key == D)
		fdf_refresh(mlx, MOVE_TO_RIGHT);
	else if (key == A)
		fdf_refresh(mlx, MOVE_TO_LEFT);
	else if (key == S)
		fdf_refresh(mlx, MOVE_UP);
	else if (key == W)
		fdf_refresh(mlx, MOVE_DOWN);
	else if (key == Z)
		fdf_refresh(mlx, ISOMETRIC);
	else
		deal_key_sub(key, mlx);
	return (SUCCESS);
}

t_point		set_point(int x, int y, int z)
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

void			draw_line_da_y(t_mlx *mlx, t_point p1, t_point p2)
{
	int i;

	mlx->bres.dx = abs(p2.x - p1.x);
	mlx->bres.dy = abs(p2.y - p1.y);
	mlx->bres.xincr = (p1.x < p2.x ? 1 : -1);
	mlx->bres.yincr = (p1.y < p2.y ? 1 : -1);
	mlx->bres.err = mlx->bres.dy / 2;
	mlx->bres.x = p1.x;
	mlx->bres.y = p1.y;
	i = 0;
	while (i++ < mlx->bres.dy)
	{
		mlx->bres.y += mlx->bres.yincr;
		mlx->bres.err += mlx->bres.dx;
		if (mlx->bres.err > mlx->bres.dy)
		{
			mlx->bres.err -= mlx->bres.dy;
			mlx->bres.x += mlx->bres.xincr;
		}
		fill_pixel(mlx->img.pixel_pos, mlx->bres.x, mlx->bres.y, p1.z);
	}
	fill_pixel(mlx->img.pixel_pos, mlx->bres.x, mlx->bres.y, p1.z);
}

void			draw_line_da_x(t_mlx *mlx, t_point p1, t_point p2)
{
	int i;

	mlx->bres.dx = abs(p2.x - p1.x);
	mlx->bres.dy = abs(p2.y - p1.y);
	mlx->bres.xincr = (p1.x < p2.x ? 1 : -1);
	mlx->bres.yincr = (p1.y < p2.y ? 1 : -1);
	mlx->bres.err = mlx->bres.dx / 2;
	mlx->bres.x = p1.x;
	mlx->bres.y = p1.y;
	i = 0;
	while (i < mlx->bres.dx)
	{
		mlx->bres.x += mlx->bres.xincr;
		mlx->bres.err += mlx->bres.dy;
		if (mlx->bres.err > mlx->bres.dx)
		{
			mlx->bres.err -= mlx->bres.dx;
			mlx->bres.y += mlx->bres.yincr;
		}
		fill_pixel(mlx->img.pixel_pos, mlx->bres.x, mlx->bres.y, p1.z);
		i++;
	}
	fill_pixel(mlx->img.pixel_pos, p1.x, p1.y, p1.z);
	fill_pixel(mlx->img.pixel_pos, p2.x, p2.y, p1.z);
}

int				draw_line(t_mlx *mlx, t_point p1, t_point p2, int cam_mode)
{
	int			dominant_axis;
	t_point	temp_p1;
	t_point	temp_p2;

	temp_p1 = p1;
	temp_p2 = p2;
	if (cam_mode == ISOMETRIC)
	{
		temp_p1.x = p1.iso_x;
		temp_p1.y = p1.iso_y;
		temp_p2.x = p2.iso_x;
		temp_p2.y = p2.iso_y;
	}
	mlx->bres.dx = abs(temp_p2.x - temp_p1.x);
	mlx->bres.dy = abs(temp_p2.y - temp_p1.y);
	dominant_axis = (mlx->bres.dx > mlx->bres.dy ? 'x' : 'y');
	if (dominant_axis == 'x')
		draw_line_da_x(mlx, temp_p1, temp_p2);
	else
		draw_line_da_y(mlx, temp_p1, temp_p2);
	return (SUCCESS);
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
		draw_line(mlx, map->p[i][j - 1], map->p[i][j], map->cam);
	if (i != 0)
		draw_line(mlx, map->p[i - 1][j], map->p[i][j], map->cam);
	return (SUCCESS);
}

int				set_points_and_draw(t_mlx *mlx, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->dep)
	{
		if (!(map->p[i] = (t_point *)malloc(sizeof(t_point) * map->len)))
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
	if (!(map->grid[line_nbr] = (int *)malloc((sizeof(int)) * map->len)))
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
	return (SUCCESS);
}

int				map_set_default_parameters(t_map *map)
{
	map->k = DEFAULT_SCALE;
	map->height_k = DEFAULT_HEIGHT_SCALE;
	map->angle_k = DEFAULT_ANGLE_MOD;
	map->cam = DEFAULT_CAM;
	map->move_x = DEFAULT_MOVE;
	map->move_y = DEFAULT_MOVE;
	return (0);
}

int				set_map(t_mlx *mlx, char *map_name)
{
	t_map	*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))) || !map_name || !(*map_name))
		return (INVAL_MEM_ERROR);
	map_set_default_parameters(map);
	if (map_parse_to_int(map_name, map) < 0)
		return (INVAL_MAP_ERROR);
	mlx->map = map;
	if (!(map->p = (t_point **)malloc(sizeof(t_point *) * map->dep)))
		return (INVAL_MEM_ERROR);
	if (set_points_and_draw(mlx, map) < 0)
		return (INVAL_MEM_ERROR);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (SUCCESS);
}

int				param_refresh_sub(t_mlx *mlx, int mode)
{
	if (mode == ANGLE_INCREASE)
		mlx->map->angle_k += 0.05;
	else if (mode == ANGLE_DECREASE)
		mlx->map->angle_k -= 0.05;
	else if (mode == ISOMETRIC)
		mlx->map->cam = ISOMETRIC;
	else if (mode == PARALLEL)
		mlx->map->cam = PARALLEL;
	else if (mode == MAP_RESET)
		map_set_default_parameters(mlx->map);
	else if (mode == EXIT)
		exit(0);
	return (SUCCESS);
}

int				param_refresh(t_mlx *mlx, int mode)
{
	if (mode == ZOOM_IN)
		mlx->map->k += 1;
	else if (mode == ZOOM_OUT)
		mlx->map->k -= (mlx->map->k == 1 ? 0 : 1);
	else if (mode == INCREASE_HEIGHT)
		mlx->map->height_k += 1;
	else if (mode == DECREASE_HEIGHT)
		mlx->map->height_k -= 1;
	else if (mode == MOVE_TO_RIGHT)
		mlx->map->move_x += 10;
	else if (mode == MOVE_TO_LEFT)
		mlx->map->move_x -= 10;
	else if (mode == MOVE_UP)
		mlx->map->move_y += 10;
	else if (mode == MOVE_DOWN)
		mlx->map->move_y -= 10;
	else
		param_refresh_sub(mlx, mode);
	return (SUCCESS);
}

int				initialize_menu(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 50, MENU_COLOR,
			"___________________________");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 70, MENU_COLOR,
			"|          MENU           |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 90, MENU_COLOR,
			"|  W A S D  ::  MOVE      |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 110, MENU_COLOR,
			"|     E     ::  +ZOOM     |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 130, MENU_COLOR,
			"|     Q     ::  -ZOOM     |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 150, MENU_COLOR,
			"|     R     ::  +HEIGHT   |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 170, MENU_COLOR,
			"|     F     ::  -HEIGHT   |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 190, MENU_COLOR,
			"|     Z     ::  ISOMETRIC |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 210, MENU_COLOR,
			"|     X     ::  PARALLEL  |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 230, MENU_COLOR,
			"|     T     ::  RESET MAP |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 250, MENU_COLOR,
			"|    ESC    ::  EXIT      |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 265, MENU_COLOR,
			"---------------------------");
	return (SUCCESS);
}

int				fdf_refresh(t_mlx *mlx, int mode)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	param_refresh(mlx, mode);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->img.pixel_pos = (unsigned int *)mlx_get_data_addr(mlx->img.img_ptr,
			&(mlx->img.size_l), &(mlx->img.bpp), &(mlx->img.endian));
	if (set_points_and_draw(mlx, mlx->map) < 0)
		return (INVAL_MEM_ERROR);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	initialize_menu(mlx);
	return (SUCCESS);
}

int				fdf_start(char *map_name)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx))))
		return (INVAL_MEM_ERROR);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Fdf");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->img.pixel_pos = (unsigned int *)mlx_get_data_addr(mlx->img.img_ptr
			, &(mlx->img.size_l), &(mlx->img.bpp), &(mlx->img.endian));
	if (set_map(mlx, map_name) < 0)
		return (INVAL_MAP_ERROR);
	initialize_menu(mlx);
	mlx_key_hook(mlx->win_ptr, deal_key, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (SUCCESS);
}

int				main(int argc, char **argv)
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
