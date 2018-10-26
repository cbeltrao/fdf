/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:02:08 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/26 16:57:25 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define HEIGHT 1200
# define WIDTH 1800
# define I_X ((900) - map->map_grid[i][0])
# define I_Y ((0) - map->map_grid[i][0] + (map->scale * i))
# define SCALE(x) (5 * x)

# define INVAL_MEM_ERROR -1
# define INVAL_MAP_ERROR -2
# define LINE_LEN_ERROR -3;

typedef struct	s_2dpoint
{
	int 		x;
	int 		y;
	int			z;
}				t_2dpoint;

typedef	struct	s_img
{
	void			*img_ptr;
	unsigned int	*img_ui;
	int				size_l;
	int				bpp;
	int				endian;
}				t_img;

typedef	struct	s_map
{
	int			**map_grid;
	int			length;
	int			depth;
	float		scale;
	t_2dpoint	**coord;
}				t_map;

typedef	struct	s_mlx
{
	void 		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}				t_mlx;

#endif
