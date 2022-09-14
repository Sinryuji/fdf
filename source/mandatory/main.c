/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:24:19 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/14 17:38:16 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../lib/libft/include/libft.h"
#include "../../lib/minilibx_opengl_20191021/mlx.h"
#include <fcntl.h>

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

void	print_image(void)
{
	t_mlx	mlx;
	t_data	img;
	int		x;
	int		y;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 500, 500, "Hello world!");
	img.img = mlx_new_image(mlx.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
	x = -1;
	while (++x < 500)
	{
		y = -1;
		while (++y < 500)
			pixel_set(&img, x, y, 0x00FF0000);
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.mlx);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;

	if (argc != 2)
		ft_puterr("Invalid number of factors.\nUsage: ./fdf [fdf file]\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_puterr("Map reading error\n");
	map = init_map();
	read_map(map, fd);
	
	return (0);
}
