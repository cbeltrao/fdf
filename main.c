/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:54:03 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/26 18:43:45 by cbeltrao         ###   ########.fr       */
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
t_2dpoint	set_point(int x, int y, int z)
{
	t_2dpoint temp;
	temp.x= x;
	temp.y = y;
	temp.z = z;
	return temp;
}

static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	ft_swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	fill_pixel(unsigned int *img, int x, int y, int z)
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

// Bresenhams functions are too long and have to may variables - redo
/* Bresenhams Algorithm to draw a line dy being the dominant axis*/
void	draw_line_da_y(t_mlx *mlx,
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
	dy = abs(initial_p.y - final_p.y);
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
		//mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, 0XFF00FF);
		fill_pixel(mlx->img.img_ui, x, y, initial_p.z);
	}
	//mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, 0XFF00FF);
	fill_pixel(mlx->img.img_ui, x, y, initial_p.z);
}


/* Bresenhams Algorithm to draw a line dx being the dominant axis*/
void	draw_line_da_x(t_mlx *mlx,
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
		fill_pixel(mlx->img.img_ui, x, y, initial_p.z);
		i++;
	}
	fill_pixel(mlx->img.img_ui, initial_p.x, initial_p.y, initial_p.z);
	fill_pixel(mlx->img.img_ui, final_p.x, final_p.y, final_p.z);
}

int		draw_line(t_mlx *mlx, t_2dpoint initial_p,
	   	t_2dpoint final_p)
{
	int dx;
	int dy;
	int dominant_axis;

	dx = abs(final_p.x - initial_p.x);
	dy = abs(final_p.y - initial_p.y);
	dominant_axis = (dx > dy ? 'x' : 'y');
	if (dominant_axis == 'x')
		draw_line_da_x(mlx, initial_p, final_p);
	else
		draw_line_da_y(mlx, initial_p, final_p);
	return (0);
}


int		draw_grid(t_mlx *mlx, t_map *map)
{
	int i;
	int j;

	i = 0;
	if(!(map->coord = (t_2dpoint **)malloc(sizeof(t_2dpoint *) * map->depth)))
		return (INVAL_MEM_ERROR);
	while (i < map->depth)
	{
		if(!(map->coord[i] = (t_2dpoint *)malloc(sizeof(t_2dpoint) * map->length)))
			return(INVAL_MEM_ERROR);
		j = 0;
		while (j < map->length)
		{
			if (j == 0)
			{
				map->coord[i][j] = set_point(I_X, I_Y, map->map_grid[i][j] * SCALE(1));
				iso(&map->coord[i][j].x, &map->coord[i][j].y, map->coord[i][j].z);
			}
			else if (j > 0)
			{
				map->coord[i][j] = set_point(I_X - map->map_grid[i][j]+ (map->scale * j),
						I_Y - map->map_grid[i][j], map->map_grid[i][j] * SCALE(1));
				iso(&map->coord[i][j].x, &map->coord[i][j].y, map->coord[i][j].z);
				draw_line(mlx, map->coord[i][j - 1], map->coord[i][j]);
			}
			if (i != 0)
				draw_line(mlx, map->coord[i - 1][j], map->coord[i][j]);
			j++;
		}
		i++;
	}
	(void)iso(&i, &j, i);
	return (0);
}

int		grid_add_line(t_map *map, char *line, int line_nbr)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!line || !(tmp = ft_strsplit(line, ' ')))
		return (INVAL_MEM_ERROR);
	while (*(tmp + i)) // Total amount of strings = total amount of numbers in a line
		i++;
	if (line_nbr > 0 && i != map->length) // Check for different line lengths
		return (INVAL_MAP_ERROR);
	map->length = i;
	if (!(map->map_grid[line_nbr] = (int *)malloc((sizeof(int)) * map->length)))
		return (INVAL_MEM_ERROR);
	i = 0;
	while (*(tmp + i))
	{
		map->map_grid[line_nbr][i] = ft_atoi(*(tmp + i));	// Parsing numbers in strings to ints
		free(*(tmp + i++));
	}
	free(tmp);
	return (0);
}

int		line_count(char *map_name)
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

// Does the parsing from .fdf to int ** and stores it into t_map *map
int		read_map(char *map_name, t_map *map)
{
	int		fd;
	int		line_nbr;
	char	*line;

	if ((line_nbr = line_count(map_name)) < 0)	// Get the number of lines in map file
		return (INVAL_MAP_ERROR);
	if ((fd = open(map_name, O_RDONLY)) < 0)	
		return (INVAL_MAP_ERROR);
	map->depth = line_nbr; 				// Depth of matrix = number of lines in map file
	if (!(map->map_grid = (int **)malloc(sizeof(int*) * line_nbr)))
		return (INVAL_MEM_ERROR);
	line_nbr = 0;
	while (get_next_line(fd, &line))	// Allocate memory for each row in map->map_grid[x]
	{
	   	if ((grid_add_line(map, line, line_nbr)) < 0)
			return (INVAL_MAP_ERROR);
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

int		set_map(t_mlx *mlx, char *map_name)
{
	t_map	*map;	

	if(!(map = (t_map *)malloc(sizeof(t_map))) || !map_name || !(*map_name)) 
		return (INVAL_MEM_ERROR);
	map->scale = SCALE(2);	// Default scale but can be changed by user input(where?)
	if(read_map(map_name, map) < 0)
		return (-1);
	if(draw_grid(mlx, map) < 0)
		return (-1);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (0);
}

// Destroy current image if there's one
// Creates a new one
/*
int		new_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img->img_ptr);
	mlx->img->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->win_ptr,
		   								mlx->img->img_ptr, 0, 0);

}
*/

int		fdf_start(char *map_name)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx))))
		return (INVAL_MEM_ERROR);
	// Initialize connection with graphical server
	mlx->mlx_ptr = mlx_init();
	// Initialize window
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Fdf");
	// Initialize image
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->img.img_ui = (unsigned int *)mlx_get_data_addr(mlx->img.img_ptr
			, &(mlx->img.size_l), &(mlx->img.bpp), &(mlx->img.endian));
	if (set_map(mlx, map_name) < 0)
		return (INVAL_MAP_ERROR);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
			400, 300, 0XFF00FF, "Belo chupa orla");
	mlx_key_hook(mlx->win_ptr, deal_key, (void *)0);
	mlx_mouse_hook(mlx->win_ptr, deal_key, (void *)0);
	mlx_loop(mlx->mlx_ptr);
	return (1);
}

int		main(int argc, char **argv)
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
