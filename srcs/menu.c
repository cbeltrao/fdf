/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 00:40:48 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/29 01:48:02 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include <mlx.h>

int				menu_select_sub(t_mlx *mlx, int option)
{
	if (option == ANGLE_INCREASE)
		mlx->map->angle_k += 0.05;
	else if (option == ANGLE_DECREASE)
		mlx->map->angle_k -= 0.05;
	else if (option == ISOMETRIC)
		mlx->map->cam = ISOMETRIC;
	else if (option == PARALLEL)
		mlx->map->cam = PARALLEL;
	else if (option == MAP_RESET)
		map_set_default_parameters(mlx->map);
	else if (option == EXIT)
		exit(0);
	return (SUCCESS);
}

int				menu_select(t_mlx *mlx, int option)
{
	if (option == ZOOM_IN)
		mlx->map->k += 1;
	else if (option == ZOOM_OUT)
		mlx->map->k -= (mlx->map->k == 1 ? 0 : 1);
	else if (option == INCREASE_HEIGHT)
		mlx->map->height_k += 1;
	else if (option == DECREASE_HEIGHT)
		mlx->map->height_k -= 1;
	else if (option == MOVE_TO_RIGHT)
		mlx->map->move_x += 10;
	else if (option == MOVE_TO_LEFT)
		mlx->map->move_x -= 10;
	else if (option == MOVE_UP)
		mlx->map->move_y += 10;
	else if (option == MOVE_DOWN)
		mlx->map->move_y -= 10;
	else
		menu_select_sub(mlx, option);
	return (SUCCESS);
}

int				deal_key_sub(int key, t_mlx *mlx)
{
	if (key == X)
		fdf_new_image(mlx, PARALLEL);
	else if (key == I)
		fdf_new_image(mlx, ANGLE_INCREASE);
	else if (key == O)
		fdf_new_image(mlx, ANGLE_DECREASE);
	else if (key == ESC)
		fdf_new_image(mlx, EXIT);
	else if (key == T)
		fdf_new_image(mlx, MAP_RESET);
	return (SUCCESS);
}

int				deal_key(int key, t_mlx *mlx)
{
	if (key == E)
		fdf_new_image(mlx, ZOOM_IN);
	else if (key == Q)
		fdf_new_image(mlx, ZOOM_OUT);
	else if (key == R)
		fdf_new_image(mlx, INCREASE_HEIGHT);
	else if (key == F)
		fdf_new_image(mlx, DECREASE_HEIGHT);
	else if (key == D)
		fdf_new_image(mlx, MOVE_TO_RIGHT);
	else if (key == A)
		fdf_new_image(mlx, MOVE_TO_LEFT);
	else if (key == S)
		fdf_new_image(mlx, MOVE_UP);
	else if (key == W)
		fdf_new_image(mlx, MOVE_DOWN);
	else if (key == Z)
		fdf_new_image(mlx, ISOMETRIC);
	else
		deal_key_sub(key, mlx);
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
