/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:02:08 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/29 01:55:30 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HEIGHT 1200
# define WIDTH 1800
# define INITIAL_X_POS (WIDTH / 3)
# define INITIAL_Y_POS (HEIGHT / 6)
# define DEFAULT_SCALE 5
# define DEFAULT_HEIGHT_SCALE 1
# define DEFAULT_ANGLE_MOD 0
# define DEFAULT_MOVE 0
# define REFRESH 100
# define INITIAL 101
# define PARALLEL 1
# define ISOMETRIC 2
# define DEFAULT_CAM PARALLEL
# define ZOOM_IN 3
# define ZOOM_OUT 4
# define INCREASE_HEIGHT 5
# define DECREASE_HEIGHT 6
# define MOVE_TO_RIGHT 7
# define MOVE_TO_LEFT 8
# define MOVE_UP 9
# define MOVE_DOWN 10
# define ANGLE_INCREASE 199
# define ANGLE_DECREASE 198
# define MAP_RESET 200
# define INVAL_MEM_ERROR -1
# define INVAL_MAP_ERROR -2
# define LINE_LEN_ERROR -3
# define SUCCESS 0
# define E 14
# define Q 12
# define R 15
# define T 17
# define F 3
# define D 2
# define A 0
# define S 1
# define W 13
# define Z 6
# define X 7
# define I 34
# define O 31
# define ESC 53
# define EXIT -1
# define MENU_COLOR 0XFF6D8A

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			orig_x;
	int			orig_y;
	int			iso_x;
	int			iso_y;
}				t_point;

typedef	struct	s_img
{
	void			*img_ptr;
	unsigned int	*pixel_pos;
	int				size_l;
	int				bpp;
	int				endian;
}				t_img;

typedef struct	s_bresen
{
	int			dx;
	int			dy;
	int			x;
	int			y;
	int			xincr;
	int			yincr;
	int			err;
}				t_bresen;

typedef	struct	s_map
{
	int			**grid;
	int			move_x;
	int			move_y;
	int			len;
	int			dep;
	int			cam;
	float		k;
	float		angle_k;
	int			height_k;
	t_point		**p;
}				t_map;

typedef	struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_length;
	int			win_depth;
	t_img		img;
	t_map		*map;
	t_bresen	bres;
}				t_mlx;

int				fdf_new_image(t_mlx *mlx, int option);

t_point			set_point(int x, int y, int z);

void			fill_pixel(unsigned int *img, int x, int y, int z);

void			draw_line_da_y(t_mlx *mlx, t_point p1, t_point p2);

void			draw_line_da_x(t_mlx *mlx, t_point p1, t_point p2);

int				bresenham_draw_line(t_mlx *mlx, t_point p1, t_point p2, int cam_option);

int				set_coords_and_draw(t_mlx *mlx, t_map *map, int i, int j);

int				set_points_and_draw(t_mlx *mlx, t_map *map);

int				grid_add_line(t_map *map, char *line, int line_nbr);

int				line_count(char *map_name);

int				map_parse_to_int(char *map_name, t_map *map);

int				map_set_default_parameters(t_map *map);

int				set_map(t_mlx *mlx, char *map_name);

int				new_image(t_mlx *mlx, int option);

int				fdf_start(char *map_name);

int				menu_select(t_mlx *mlx, int option);

int				menu_select_sub(t_mlx *mlx, int option);

int				deal_key(int key, t_mlx *mlx);

int				deal_key_sub(int key, t_mlx *mlx);

int				initialize_menu(t_mlx *mlx);

#endif
