/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:54:03 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/09/25 13:28:18 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		deal_key(int key, void *param)
{
	ft_putchar(key);
	ft_putchar('x');
	(void)param;
   	return (0);
}

/* Set point variables */
void	set_point(t_2dpoint *point, int x, int y)
{
	point->x= x;
	point->y = y;
}

/* Function to set the dominant axis to be used in the Bresenhams Algorithm */
int set_da(int delta_x, int delta_y)
{
	if (delta_x >= delta_y)
		return ('x');
	else
		return ('y');
}

void	ft_swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* Bresenhams Algorithm to draw a line */
void	draw_line_da_x(void *mlx_ptr, void *win_ptr,
	   	t_2dpoint initial_p, t_2dpoint final_p)
{
	int x;
	int y;
	int dx;
	int dy;
	int xincr, yincr;
	int err;
	int i;

	dx = abs(final_p.x - initial_p.x);
	dy = abs(final_p.y - initial_p.y);

	xincr = (initial_p.x < final_p.x ? 1 : -1);	
	/* if (initial_p.x < final_p.x)
		xincr = 1;
	else
		xincr = -1;
	*/
	yincr = (initial_p.y < final_p.y ? 1 : -1);
	/* if (initial_p.y < final_p.y)
		yincr = 1;
	else
		yincr = -1;
	*/
	x = initial_p.x;
	y = initial_p.y;
	if (dx > dy)
	{
		err = dx / 2;
		i = 0;
		while (i < dx)
		{
			x += xincr;
			err += dy;
			if (err > dx)
			{
				err -= dx;
				y += yincr;
			}	
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
			i++;
		}
	}
	else
	{
		err = dy / 2;
		i = 0;
		while (i < dy)
		{
			y += yincr;
			err += dx;
			if (err > dy)
			{
				err -= dy;
				x += xincr;
			}
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
			i++;
		}
	}
	mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
	mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
}

int		draw_line(void *mlx_ptr, void *win_ptr, t_2dpoint initial_p,
	   	t_2dpoint final_p)
{
	int delta_x;
	int delta_y;
	int dominant_axis;

	delta_x = final_p.x - initial_p.x;
	delta_y = final_p.y - initial_p.y;
	dominant_axis = set_da(delta_x, delta_y);
	/* if (dominant_axis == 'x') */
	draw_line_da_x(mlx_ptr, win_ptr, initial_p, final_p);
	return (0);
}

int main()
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_2dpoint	initial_point;
	t_2dpoint	final_point;

	/* Set point variables */
	set_point(&initial_point, 500, WIN_HEIGHT/2);
	set_point(&final_point, 800, 1);

	/* Initialize connection with graphical server */
	mlx_ptr = mlx_init();

	/* Initialize a window */
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");

	/* Initialize drawing between 2 points */
	draw_line(mlx_ptr, win_ptr, initial_point, final_point);

	/* Same as pixel_put, but puts string instead of single pixel */
	 mlx_string_put(mlx_ptr, win_ptr, 300,300, 0XFF00FF, "HOLA SIMONE");

	/* Watch for keyboard inputs */
	mlx_key_hook(win_ptr, deal_key, (void *)0);

	/* Watch for mouse inputs */
	/* mlx_mouse_hook(win_ptr, deal_key, (void *)0); */

	/* Listen for events */
	mlx_loop(mlx_ptr);
	return (0);
}
