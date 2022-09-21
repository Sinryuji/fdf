/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:24:19 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/21 15:45:37 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../lib/libft/include/libft.h"
#include "../../lib/minilibx_opengl_20191021/mlx.h"
#include <math.h>
#include <fcntl.h>

void	pixel_set(t_fdf *fdf, int x, int y, int color)
{
	char	*pixel;

	pixel = fdf->addr + (y * fdf->line_length + x * \
	(fdf->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

int	key_hook(int key_code, t_fdf *fdf)
{
	if (key_code == 53)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		exit(0);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)
		printf("x : %d y : %d\n", x, y);
	if (button == 4)
	{
		fdf->map->map_width *= 0.9;
		fdf->map->map_height *= 0.9;
		print_image(fdf->map, fdf);
	}
	if (button == 5)
	{
		fdf->map->map_width *= 1.1;
		fdf->map->map_height *= 1.1;
		print_image(fdf->map, fdf);
	}
	return (0);
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
//		mlx_pixel_put(fdf->mlx, fdf->win, p1.x, p1.y, 0x00FFFFFF);
		i++;
	}
}

double	get_ratio(t_map *map, int n)
{
	double	ratio;
	double	x;
	double	d;

	x = map->map_width / 3;
	d = x * 2 - x;
	ratio = d / (map->width - 1) / d;
	return (ratio * n);
}

t_point	get_point(t_map *map, int i, int j)
{
	double	x;
	double	y;
	t_point	new;

	x = map->map_width / 3;
	y = map->map_height / 3;
	x += (x * 2 - x) * get_ratio(map, i);
	y += (y * 2 - y) * get_ratio(map, j);
	new.x = x;
	new.y = y;
	new.z = map->z_arr[j * map->height + i];
	isometric(&new.x, &new.y, new.z);
	new.x += map->map_width / 3;
	new.y -= map->map_height / 5;
	return (new);
}

void	pixel_clear(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map->map_width)
	{
		j = 0;
		while (j < fdf->map->map_height)
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

int	main(int argc, char **argv)
{
	int		fd;
	t_fdf	*fdf;

	if (argc != 2)
		put_error(ERR_USAGE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		put_error(ERR_OPEN);
	fdf = fdf_init();
	fdf->map = read_map(fd);
	print_image(fdf->map, fdf);
	mlx_key_hook(fdf->win, key_hook, fdf);
	mlx_mouse_hook(fdf->win, mouse_hook, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
