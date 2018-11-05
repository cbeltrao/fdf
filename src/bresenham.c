/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 01:06:05 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/29 01:54:19 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

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

int				bresenham_draw_line(t_mlx *mlx, t_point p1, t_point p2,
									int cam_option)
{
	int			dominant_axis;
	t_point		temp_p1;
	t_point		temp_p2;

	temp_p1 = p1;
	temp_p2 = p2;
	if (cam_option == ISOMETRIC)
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
