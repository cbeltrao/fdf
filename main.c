/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:54:03 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/24 14:54:25 by cbeltrao         ###   ########.fr       */
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

int		deal_key(int key, void *param)
{
	ft_putchar(key);
	ft_putchar('x');
	(void)param;
   	return (0);
}

/* Set point variables */
t_2dpoint	set_point(int x, int y)
{
	t_2dpoint temp;
	temp.x= x;
	temp.y = y;
	return temp;
}

void	ft_swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}


// Bresenhams functions are too long and have to may variables - redo
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

int		draw_grid(void *mlx_ptr, void *win_ptr, t_map *map)
{
	int	scale;
	int i;
	int j;

	scale = 20;
	i = 0;
	j = 0;
	if(!(map->coord_grid = (t_2dpoint **)malloc(sizeof(t_2dpoint *) * map->depth)))
		return (INVAL_MEM_ERROR);
	// Set up grid
	while (i < map->depth)
	{
		if(!(map->coord_grid[i] = (t_2dpoint *)malloc(sizeof(t_2dpoint) * map->length)))
			return(INVAL_MEM_ERROR);
		j = 0;
		while (j < map->length)
		{
			if (j == 0)
				map->coord_grid[i][j] = set_point(WIN_WIDTH / 3, (WIN_HEIGHT / 3 + scale * i ));
			// Now every following point will be based on the precedent X,Y
			else if (j > 0)
			{
				// Set point on grid(scaled)
				map->coord_grid[i][j] = set_point(map->coord_grid[i][j - 1].x + scale, map->coord_grid[i][0].y);
				// Draw lines
				draw_line(mlx_ptr, win_ptr, map->coord_grid[i][j - 1], map->coord_grid[i][j]);
			}
			// Draw columns
			if (i != 0)
				draw_line(mlx_ptr, win_ptr, map->coord_grid[i - 1][j], map->coord_grid[i][j]);
			j++;
		}
		i++;
	}
	return (0);
}

int		grid_add_line(t_map *map, char *line, int line_nbr)
{
	char	**tmp;
	int		i;

	i = 0;
	if(!line || !(tmp = ft_strsplit(line, ' ')))
		return (INVAL_MEM_ERROR);
	// Counting how many strings("ints") there are in total
	// So we can know what to allocate
	// for the size of each int array in the matrix 
	while(*(tmp + i))
		i++;
	map->length = i;
	if(!(map->map_grid[line_nbr] = (int *)malloc((sizeof(int)) * map->length)))
		return (INVAL_MEM_ERROR);
	i = 0;
	while(*(tmp + i))
	{
		map->map_grid[line_nbr][i] = ft_atoi(*(tmp + i));	
		free(*(tmp + i++));
	}
	free(tmp);
	return (0);
}

int		line_count(char *map_name)
{
	int lines;
	char *line;
	int fd;

	lines = 0;
	if((fd = open(map_name, O_RDONLY)) < 0)
		return (INVAL_MAP_ERROR);
	while (get_next_line(fd, &line))
		lines++;
	close(fd);
	return (lines);
}

// Does the parsing from .fdf to int ** and stores it into t_map *map
int		read_map(char *map_name, t_map *map)
{
	int		fd;
	int		line_nbr;
	char	*line;

	if((line_nbr = line_count(map_name)) < 0)	// Get the number of lines in map file
		return (INVAL_MAP_ERROR);
	if((fd = open(map_name, O_RDONLY)) < 0)	
		return (INVAL_MAP_ERROR);
	map->depth = line_nbr; 				// Depth of matrix = number of lines in map file
	if(!(map->map_grid = (int **)malloc(sizeof(int*) * line_nbr)))
		return (INVAL_MEM_ERROR);
	line_nbr = 0;
	// In this loop we can(if not here somewhere else)
	// check for erros like wrong input
	// Or different sized lines
	while (get_next_line(fd, &line))	// Allocate memory for each row in map->map_grid[x]
	{
	   	grid_add_line(map, line, line_nbr);
		line_nbr++;
   	}
	close(fd); 
	return (0); 
}


void	TEST_print_map(t_map *map) // Test if parsing(.fdf ~ map->map_grid was successful
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < map->depth)
	{
		j = 0;
		while(j < map->length)
		{
			printf("%d  ", map->map_grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

	// Responsible for setting up the t_map structure
	// Which should contain:
	// .fdf map parsed to a int ** matrix map,
	// The length and depth of the matrix
	// And int ** coordinates matrix containing x, y positions for
	// each element in the matrix map, so we can send the coordinates 
	// matrix to the draw_grid function

int		set_map(void *mlx_ptr, void *win_ptr, char *map_name)
{
	t_map	*map;	

	if(!(map = (t_map *)malloc(sizeof(t_map))) || !map_name || !(*map_name)) 
		return (INVAL_MEM_ERROR);
	if(read_map(map_name, map) < 0)
		return (-1);
	if(draw_grid(mlx_ptr, win_ptr, map) < 0)
		return (-1);
	/*-- Testing Functions --*/
	TEST_print_map(map);
	/*-- end of testing functions --*/
	return (0);
}

int		fdf_start(char	*map_name)
{
	t_mlx	*mlx;

	if(!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (INVAL_MEM_ERROR);
	// Initialize connection with graphical server
	mlx->mlx_ptr = mlx_init();
	// Initialize window
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Fdf");

	if(set_map(mlx->mlx_ptr, mlx->win_ptr, map_name) < 0)
		return (INVAL_MAP_ERROR);

	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 400, 300, 0XFF00FF, "Belo chupa orla");
	
	mlx_key_hook(mlx->win_ptr, deal_key, (void *)0);

	mlx_mouse_hook(mlx->win_ptr, deal_key, (void *)0);

	mlx_loop(mlx->mlx_ptr);
	return (1);
}

int main(int argc, char **argv)
{

	(void)argc;	
	//mlx_ptr = mlx_init();	// Initialize Connection with graphical server

	//win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF"); // Initialize Window

	//-- Beginning of tests --//
	//if(set_map(mlx_ptr, win_ptr, argv[1]) < 0) // Parses .fdf to map and coord grids and prints it
	if (fdf_start(argv[1]) < 0)
		return (-1);
	//--    End of test		--//
	
	//mlx_string_put(mlx_ptr, win_ptr, 400,300, 0XFF00FF, "Belo chupa rola"); // Print string *test*

	//mlx_key_hook(win_ptr, deal_key, (void *)0); // Watch for keyboard inputs

	//mlx_mouse_hook(win_ptr, deal_key, (void *)0); // Watch for mouse inputs

	//mlx_loop(mlx_ptr);		// Listen for events
	return (0);
}
