/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:24:19 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/18 17:46:53 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../lib/libft/include/libft.h"
#include "../../lib/minilibx_opengl_20191021/mlx.h"
#include <math.h>

void	pixel_set(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length + x * \
	(data->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

int	key_hook(int key_code, t_mlx *mlx)
{
	if (key_code == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}

t_dot	get_dot(int x, int y, t_map *map)
{
	t_dot	new;
	int		width;
	int		height;

	width = 0;
	height = 0;
	new.x = x;
	new.y = y;
	while (x > WIDTH / 3)
	{
		width++;
		x -= WIDTH / 3 / map->width;
	}
	while (y > HEIGHT / 3)
	{
		height++;
		y -= HEIGHT / 3 / map->height;
	}
	new.z = map->map[height * 10 + width].value;
	new.color = map->map[height * 10 + width].color;
	return (new);
}

void	dda(t_data *img, t_mlx *mlx, t_dot dot1, t_dot dot2)
{
	double	dx;
	double	dy;
	double	step;
	double	i;

	(void)img;
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
		mlx_pixel_put(mlx->mlx, mlx->win, dot1.x, dot1.y, 0x00FFFFFF);
		i++;
	}
}

void	print_line(t_data *img, t_mlx *mlx, t_map *map, double x, double y)
{
	t_dot	dot1;
	t_dot	dot2;

	dot2 = get_dot(x, y, map);
	if (x > WIDTH / 3)
	{
		dot1 = get_dot(x - WIDTH / 3 / map->width, y, map);
		isometric(&dot1.x, &dot1.y, dot1.z);
		dda(img, mlx, dot1, dot2);
	}
	if (y > HEIGHT / 3)
	{
		dot1 = get_dot(x, y - HEIGHT / 3 / map->height, map);
		isometric(&dot1.x, &dot1.y, dot1.z);
		dda(img, mlx, dot1, dot2);
	}
}

void	print_image(t_map *map, t_mlx *mlx, t_data *img)
{
	double	x;
	double	y;
	double	i;
	double	j;

	x = WIDTH / 3;
	i = 0;
	while (x < WIDTH / 3 * 2 && i < map->width)
	{
		y = HEIGHT / 3;
		j = 0;
		while (y < HEIGHT / 3 * 2 && j < map->height)
		{
			if (x == WIDTH / 3 + (WIDTH / 3 / map->width * i) \
					&& y == HEIGHT / 3 + (HEIGHT / 3 / map->height * j))
			{
				print_line(img, mlx, map, x, y);
				j++;
				if (j == map->height)
					i++;
			}
			y++;
		}
		x++;
	}
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_mlx	*mlx;
	t_data	*img;

	if (argc != 2)
		put_error(ERR_USAGE);
	map = read_map(argv[1]);
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	img = (t_data *)malloc(sizeof(t_data));
	if (!mlx || !img)
		put_error(ERR_MALLOC);
	mlx_img_init(mlx, img);
	print_image(map, mlx, img);
//	mlx_put_image_to_window(mlx->mlx, mlx->win, img->img, 0, 0);
	mlx_key_hook(mlx->win, key_hook, mlx);
	mlx_loop(mlx->mlx);
	map_free(map, 0);
	return (0);
}
