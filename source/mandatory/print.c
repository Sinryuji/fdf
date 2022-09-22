/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:23:03 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/22 18:27:39 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../lib/minilibx_opengl_20191021/mlx.h"
#include <math.h>

void	pixel_set(t_fdf *fdf, int x, int y, int color)
{
	char	*pixel;

	if (x >= WIDTH || x <= 0 || y >= HEIGHT || y <= 0)
		return ;
	pixel = fdf->addr + (y * fdf->line_length + x * \
	(fdf->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	dda(t_fdf *fdf, t_point p1, t_point p2)
{
	double	dx;
	double	dy;
	double	step;
	double	i;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	i = 0;
	pixel_set(fdf, p1.x, p1.y, 0x00FFFFFF);
	while (i <= step)
	{
		p1.x += dx / step;
		p1.y += dy / step;
		pixel_set(fdf, p1.x, p1.y, 0x00FFFFFF);
		i++;
	}
}

t_point	get_point(t_map *map, int i, int j)
{
	t_point	new;

	new.x = map->gap * i;
	new.y = map->gap * j;
	new.z = map->z_arr[j * map->height + i] * map->gap / 2;
	isometric(&new.x, &new.y, new.z);
	new.x += (double)WIDTH / 2;
	new.y += (double)HEIGHT / 3;
	return (new);
}

void	pixel_clear(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			pixel_set(fdf, i, j, 0);
			j++;
		}
		i++;
	}
}

void	print_image(t_map *map, t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	pixel_clear(fdf);
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
		{
			if (i < map->width - 1)
				dda(fdf, get_point(map, i, j), get_point(map, i + 1, j));
			if (j < map->height - 1)
				dda(fdf, get_point(map, i, j), get_point(map, i, j + 1));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
