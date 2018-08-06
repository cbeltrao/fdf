/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:54:03 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/08/06 20:03:41 by cbeltrao         ###   ########.fr       */
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

// Set point variables
void	set_point(t_point *point, int xlx, int yy)
{
	point->x= xlx;
	point->y = yy;
}

// Function to set the dominant axis to be used in the Bresenhams Algorithm
int set_da(int delta_x, int delta_y)
{
	if (delta_x >= delta_y)
		return ('x');
	else
		return ('y');
}

// Bresenhams Algorithm to draw a line
void	draw_line_da_x(void *mlx_ptr, void *win_ptr, t_point *initial_p, t_point *final_p)
{
	float m;
	float e;
	int x;
	int delta_x;
	int y;
	int delta_y;

	printf("final_p.y: %d, inital_p.y: %d |||| final_p.x: %d, initial_p.x: %d\n\n"
			, final_p->y, initial_p->y, final_p->x, initial_p->x);

	delta_x = final_p->x - initial_p->x;
	delta_y = final_p->y - initial_p->y;

	printf("delta_x: %d || delta_y: %d\n", delta_x, delta_y);
	m = (float)delta_x/delta_y;
	printf("## m is: %.2f ##\n\n\n", m);
	x = initial_p->x;
	y = initial_p->y;
	e = m - 1.0;
	
	// Test to see if function is rolling
	while(x < final_p->x - 1)
	{
		fflush(0);
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
		if ( e >= 0)
		{
			ft_putchar('L');
			y += 1;
			e -= 1.0;
		}
		x += 1;
		e += m;
	}
	mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
}

int		draw_line(void *mlx_ptr, void *win_ptr, t_point *initial_p, t_point *final_p)
{
	int delta_x;
	int delta_y;
	int dominant_axis;

	delta_x = final_p->x - initial_p->x;
	delta_y = final_p->y - initial_p->y;
	dominant_axis = set_da(delta_x, delta_y);
	//if (dominant_axis == 'x')

	draw_line_da_x(mlx_ptr, win_ptr, initial_p, final_p);
	return (0);
}

int main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_point	initial_point;
	t_point final_point;

	// Set point variables
	set_point(&initial_point, 250, 250);
	set_point(&final_point, 285, 275);
	// Initialize connection with graphical server
	mlx_ptr = mlx_init();

	// Initialize a window
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "FdF");

	// Initialize drawing
	draw_line(mlx_ptr, win_ptr, &initial_point, &final_point);

	// Connect to the graphical server through mlx_ptr, and
	// place a pixel at win_ptr window,
	// at coordinates 'x' and 'y', of color '0X...'
	//mlx_pixel_put(mlx_ptr, win_ptr, win_ptr->size_x/2, win_ptr->size_y/2, 0xFFFFFF);

	// Same as pixel_put, but puts string instead of single pixel
	//mlx_string_put(mlx_ptr, win_ptr, 300,300, 0XFF00FF, "HOLA SIMONE");

	// Watch for keyboard inputs
	//	mlx_key_hook(win_ptr, deal_key, (void *)0);

	// Watch for mouse inputs
	//mlx_mouse_hook(win_ptr, deal_key, (void *)0);

	// Listen for events
	mlx_loop(mlx_ptr);
	return (0);
}
