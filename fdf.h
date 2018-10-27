/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:02:08 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/27 13:42:18 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define HEIGHT 1200
# define WIDTH 1800
# define I_X ((900) - map->grid[i][0])
# define I_Y ((0) - map->grid[i][0] + (map->k * i))
# define SCALE(x) (2 * x)

# define INVAL_MEM_ERROR -1
# define INVAL_MAP_ERROR -2
# define LINE_LEN_ERROR -3;

typedef struct	s_2dpoint
{
	int 		x;
	int 		y;
	int			iso_x;
	int			iso_y;
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
	int			**grid;
	int			move_x;
	int			move_y;
	int			len;
	int			dep;
	float		k; // scale
	int			z_h; // height exclusive scale
	t_2dpoint	**p;
}				t_map;

typedef	struct	s_mlx
{
	void 		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_map		*map;
}				t_mlx;

#endif
