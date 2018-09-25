/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:54:03 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/09/25 13:05:22 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "fdf.h"
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
	   	t_2dpoint *initial_p, t_2dpoint *final_p)
{
	float e;
	int x;
	int delta_x;
	int y;
	int delta_y;

	delta_x = final_p->x - initial_p->x;
	delta_y = final_p->y - initial_p->y;
	
	if (initial_p->x > final_p->x)
		ft_swap(&initial_p->x, &final_p->x);
	if (initial_p->y > final_p->y)
		ft_swap(&initial_p->y, &final_p->y);
	printf("asdasd %d %d", initial_p->x, final_p->x);
	fflush(stdout);
	x = initial_p->x;
	y = initial_p->y;

	delta_x = (delta_x == 0) ? 1 : delta_x;
	delta_y = (delta_y == 0) ? 1 : delta_y;
	e = (float)(delta_x / delta_y) - 1.0;

	while(x < final_p->x - 1 || y != final_p->y > y - 1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
		if ( e >= 0)
		{
			y += 1;
			e -= 1.0;
		}
		x += 1;
		e += (float)delta_x / delta_y;
	}
	mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
}

int		draw_line(void *mlx_ptr, void *win_ptr, t_2dpoint *initial_p,
	   	t_2dpoint *final_p)
{
	int delta_x;
	int delta_y;
	int dominant_axis;

	delta_x = final_p->x - initial_p->x;
	delta_y = final_p->y - initial_p->y;
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
	set_point(&initial_point, 500, WIN_HEIGHT / 2);
	set_point(&final_point, 300, WIN_HEIGHT);

	/* Initialize connection with graphical server */
	mlx_ptr = mlx_init();

	/* Initialize a window */
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");

	/* Initialize drawing between 2 points */
	draw_line(mlx_ptr, win_ptr, &initial_point, &final_point);

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
