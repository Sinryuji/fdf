/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:24:32 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/23 20:43:59 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "error.h"
# include <stdio.h>

# define WIDTH 1280
# define HEIGHT 720

typedef struct s_fdf
{
	void			*mlx;
	void			*win;	
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	struct s_map	*map;
}	t_fdf;

typedef struct s_map
{
	int		width;
	int		height;
	int		*z_arr;
	int		*color_arr;
	double	gap;
	double	x_move;
	double	y_move;
}	t_map;

typedef struct s_data
{
	int				z;
	int				color;
	struct s_data	*next;
}	t_data;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point;

/* map.c */
t_map	*read_map(int fd);
void	map_free(t_map *map, int err_code);

/* fdf.c */
t_fdf	*fdf_init(void);

/* stack.c */
void	push(t_data **data, int z, int color);
void	data_to_arr(t_map *map, t_data *data);

/* projection.c */
void	isometric(double *x, double *y, double z);
void	map_move(int key_code, t_map *map);

/* hook.c */
int		key_hook(int key_code, t_fdf *fdf);
int		mouse_hook(int button, int x, int y, t_fdf *fdf);

/* print.c */
void	print_image(t_map *map, t_fdf *fdf);

#endif
