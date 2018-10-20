/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:54:03 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/20 23:42:56 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gnl/get_next_line.h"
#include "libft/includes/libft.h"
#include <unistd.h>

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

int		*grid_add_line(char *line, int line_len)
{
	char	**tmp;
	int		*map_line;
	int		i;

	i = 0;
	if(!line || !(tmp = ft_strsplit(line, ' ')))
		return (NULL);
	// Counting how many strings("ints") there are in total
	// So we can know what to allocate
	// for the size of each int array in the matrix 
	(void) line_len;
	while(*(tmp + i))
		i++;
	map_line = (int *)malloc((sizeof(int)) * i);

	i = 0;
	while(*tmp)
	{
		map_line[i] = ft_atoi(*tmp++);	
		printf("%d  ", map_line[i]);
		i++;
	}
	printf("\n");
	return (map_line);
}

int		line_count(char *map_name)
{
	int lines;
	char *line;
	int fd;

	lines = 0;
	fd = open(map_name, O_RDONLY);
	while (get_next_line(fd, &line))
		lines++;
	close(fd);
	return (lines);
}

int		**read_map(char *map_name)
{
	int		fd;
	int		line_nbr;
	char	*line;
	int		**map_grid;
	int		len;
	// Testing variables
	//int		test_grid_i = 0;
	//int		test_grid_j = 0;

	// Get the numbers of line so we can allocate the depth of the int matrix 
	line_nbr = line_count(map_name);
	if(!(map_grid = (int **)malloc(sizeof(int*) * line_nbr)))
		return (NULL);

	// Now we need to allocate memory for each array of the matrix 
	// According to the number of elements in the map
	// If the input is correct the number of elements will be (len + 1)/2,
	// Because every 2 elements are separated by 1 white space.
	fd = open(map_name, O_RDONLY);	
	line_nbr = 0;
	// We can check for line length differences in this loop
	// We also need to check for incorrect inputs
	while (get_next_line(fd, &line))
	{
		len = ft_strlen(line);
	   	map_grid[line_nbr] = grid_add_line(line, len);
		line_nbr++;
   	}
   	// At this point we should have a int matrix filled 
	// with every element of the map close(fd); 
	// ??? Testing printing matrix 
	/*
	while(test_grid_i < line_nbr)
   	{
		test_grid_j = 0;
		while(test_grid_j < (len / 2) + 1)
		{
			printf("map_grid[test_grid_i:%d][test_grid_j:%d]: %d\n", 
					test_grid_i, test_grid_j, map_grid[test_grid_i][test_grid_j]);
			fflush(stdout);
			test_grid_j++;
		}
		printf("##OPA\n");
		fflush(stdout);
		test_grid_i++;
	}
	*/
	return (map_grid);
}

int main()
{
	void		*mlx_ptr;
	void		*win_ptr;
	// Testing variables
	//char		*numbers = "0 1 2 3 4";
	int			line[4][6] =  { {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
	   							{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} };
	int		**test_map;

	/* Initialize connection with graphical server */
	//	mlx_ptr = mlx_init();

	// Testing grid_add_line Function
		(void)line;
		(void)win_ptr;	
		(void)mlx_ptr;
	//	numbers_atoi = grid_add_line(numbers, ft_strlen(numbers));
	
	//	Testing read_map functino
	test_map = read_map("test_maps/42.fdf");
	// Initialize a window 
	/*
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	draw_grid(mlx_ptr, win_ptr, line); // Grid setup and print

	mlx_string_put(mlx_ptr, win_ptr, 400,300, 0XFF00FF, "Belo chupa rola"); // Print string

	mlx_key_hook(win_ptr, deal_key, (void *)0); // Watch for keyboard inputs

	mlx_mouse_hook(win_ptr, deal_key, (void *)0); // Watch for mouse inputs

	//Listen for events 
	mlx_loop(mlx_ptr);
	*/
	return (0);
}
