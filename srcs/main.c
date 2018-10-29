/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 22:59:53 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/29 02:08:06 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include <mlx.h>

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

	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))) || !map_name || !(*map_name))
		return (INVAL_MEM_ERROR);
	map_set_default_parameters(map);
	if (map_parse_to_int(map_name, map) < 0)
		return (INVAL_MAP_ERROR);
	mlx->map = map;
	if (!(map->p = (t_point **)ft_memalloc(sizeof(t_point *) * map->dep)))
		return (INVAL_MEM_ERROR);
	if (set_points_and_draw(mlx, map) < 0)
		return (INVAL_MEM_ERROR);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (SUCCESS);
}

int				fdf_new_image(t_mlx *mlx, int option)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	menu_select(mlx, option);
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
