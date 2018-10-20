/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:54:03 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/09/26 19:19:36 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "gnl/get_next_line.h"
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

void	ft_swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* Bresenhams Algorithm to draw a line dy being the dominant axis*/
void	draw_line_da_y(void *mlx_ptr, void *win_ptr,
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
	i = 0;

	xincr = (initial_p.x < final_p.x ? 1 : -1);	
	yincr = (initial_p.y < final_p.y ? 1 : -1);

	x = initial_p.x;
	y = initial_p.y;
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
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
	}
	mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
	mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
}


/* Bresenhams Algorithm to draw a line dx being the dominant axis*/
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
	i = 0;
	xincr = (initial_p.x < final_p.x ? 1 : -1);	
	yincr = (initial_p.y < final_p.y ? 1 : -1);
	x = initial_p.x;
	y = initial_p.y;
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
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0XFF00FF);
		i++;
	}
	mlx_pixel_put(mlx_ptr, win_ptr, initial_p.x, initial_p.y, 0XFF00FF);
	mlx_pixel_put(mlx_ptr, win_ptr, final_p.x, final_p.y, 0XFF00FF);
}

int		draw_line(void *mlx_ptr, void *win_ptr, t_2dpoint initial_p,
	   	t_2dpoint final_p)
{
	int dx;
	int dy;
	int dominant_axis;

	dx = abs(final_p.x - initial_p.x);
	dy = abs(final_p.y - initial_p.y);
	dominant_axis = (dx > dy ? 'x' : 'y');
	if (dominant_axis == 'x')
		draw_line_da_x(mlx_ptr, win_ptr, initial_p, final_p);
	else
		draw_line_da_y(mlx_ptr, win_ptr, initial_p, final_p);
	return (0);
}

void	draw_grid(void *mlx_ptr, void *win_ptr, int grid[4][6])
{
	int	scale;
	int i;
	int j;
	int grid_width = 6;
	int grid_height = 4;
	t_2dpoint	grid_points[sizeof(grid[0])/sizeof(grid[0][0])]
							[sizeof(grid[1])/sizeof(grid[1][0])];

	scale = 50;
	i = 0;
	j = 0;
	
	// Set up grid
	while (i < grid_height)
	{
		j = 0;
		while (j < grid_width)
		{
			// Sets X,Y if it's the first point of a line
			if (j == 0)
				set_point(&grid_points[i][j], WIN_WIDTH / 3, (WIN_HEIGHT / 3 + scale * i ));
			// Now every following point will be based on the precedent X,Y
			else
			{
				// Set point on grid(scaled)
				set_point(&grid_points[i][j], grid_points[i][j - 1].x + scale, grid_points[i][0].y);
				// Draw lines
				draw_line(mlx_ptr, win_ptr, grid_points[i][j - 1], grid_points[i][j]);
			}
			// Draw columns
			if (i != 0)
				draw_line(mlx_ptr, win_ptr, grid_points[i - 1][j], grid_points[i][j]);
			j++;
		}
		i++;
	}
}

int		**grid_add_line(int	**map_grid,	char *line, int i,int line_len)
{
	char	**tmp;
	int		j;

	line_len = ft_strlen(line);
	j = 0;
	if(!line || !map_grid)
		return (void);
	tmp = ft_strsplit(line, ' ');
	*(map_grid + i) = (int *)malloc((sizeof int) * line_len);
	while(*tmp)
	{
		map_grid[i][j] = ft_atoi(*tmp++);	
		printf("map_grid[i][j]: %d", map_grid[i][j]);
		j++;
	}
	/* Print test */
	
	return (map_grid);
}

int		**read_map(char *map_name)
{
	int		fd;
	int		line_nbr;
	char	*line;
	int		**map_grid;
	int		len;

	fd = open(map_name, O_RDONLY);
	line_nbr = 0;
	while (get_next_line(fd, &line))
		line_nbr++;
	close(fd);
	map_grid = (int **)malloc((sizeof int*) * line_nbr);
	fd = open(map_name, O_RDONLY);	
	line_nbr = 0;
	while (get_next_line(fd, &line))
	{
		len = ft_strlen(line);
		map_grid = grid_add_line(map_grid, line, line_nbr, len);
		line_nbr++;
	}
	close(fd);
	fd = 0;
	while(line_nbr > 0)
	{
		while(fd < len)
		{
			printf("%d," map_grid[line_nbr][fd]); 
			fd++;
		}
		printf("\n");
		line_nbr++;
	}
}
int main()
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			line[4][6] =  { {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
	   							{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} };

	/* Initialize connection with graphical server */
	mlx_ptr = mlx_init();

	/* Initialize a window */
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");

	draw_grid(mlx_ptr, win_ptr, line); // Grid setup and print

	mlx_string_put(mlx_ptr, win_ptr, 400,300, 0XFF00FF, "Belo chupa rola"); // Print string

	mlx_key_hook(win_ptr, deal_key, (void *)0); // Watch for keyboard inputs

	mlx_mouse_hook(win_ptr, deal_key, (void *)0); // Watch for mouse inputs

	/* Listen for events */
	mlx_loop(mlx_ptr);
	return (0);
}
