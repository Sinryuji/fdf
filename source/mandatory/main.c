/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:24:19 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/19 22:37:17 by hyeongki         ###   ########.fr       */
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

void	dda(t_fdf *fdf, t_dot dot1, t_dot dot2)
{
	double	dx;
	double	dy;
	double	step;
	double	i;

	dx = dot2.x - dot1.x;
	dy = dot2.y - dot1.y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	i = 0;
	while (i <= step)
	{
		dot1.x += dx / step;
		dot1.y += dy / step;
//		pixel_set(img, dot1.x, dot1.y, 0x0000FF00);
		mlx_pixel_put(fdf->mlx, fdf->win, dot1.x, dot1.y, 0x00FFFFFF);
		i++;
	}
}

void	print_line(t_fdf *fdf, t_map *map, double x, double y)
{
	t_dot	dot1;
	t_dot	dot2;

	dot2.x = x;
	dot2.y = y;
	if (x > WIDTH / 3)
	{
		dot1.x = x - WIDTH / 3 / map->width;
		dot1.y = y;
//		isometric(&dot1.x, &dot1.y, dot1.z);
		dda(fdf, dot1, dot2);
	}
	if (y > HEIGHT / 3)
	{
		dot1.x = x;
		dot1.y = y - HEIGHT / 3/ map->height;;
//		isometric(&dot1.x, &dot1.y, dot1.z);
		dda(fdf, dot1, dot2);
	}
}

void	print_dot(t_fdf *fdf, t_map *map, int i, int j)
{
	double	x;
	double	y;
	double	x_gap;
	double	y_gap;

	x = (double)WIDTH / 4;
	y = (double)HEIGHT / 4;
	x_gap = (x * 3 - x) / (map->width - 2);
	y_gap = (y * 3 - y) / (map->height - 2);
	x += x_gap * i;
	y += y_gap * j;
	mlx_pixel_put(fdf->mlx, fdf->win, x, y, 0x00FFFFFF);
}

void	print_image(t_map *map, t_fdf *fdf)
{
	int	i;
	int	j;

//	x = WIDTH / 3;
//	i = 0;
//	while (x < WIDTH / 3 * 2 && i < map->width)
//	{
//		y = HEIGHT / 3;
//		j = 0;
//		while (y < HEIGHT / 3 * 2 && j < map->height)
//		{
//			if (x == WIDTH / 3 + (WIDTH / 3 / map->width * i) \
//					&& y == HEIGHT / 3 + (HEIGHT / 3 / map->height * j))
//			{
//				print_line(fdf, map, x, y);
//				j++;
//				if (j == map->height)
//					i++;
//			}
//			y++;
//		}
//		x++;
//	}
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
		{
			print_dot(fdf, map, i, j);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
	t_fdf	*fdf;

	if (argc != 2)
		put_error(ERR_USAGE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		put_error(ERR_OPEN);
	map = read_map(fd);
	fdf = fdf_init();
	print_image(map, fdf);
//	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	mlx_key_hook(fdf->win, key_hook, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
