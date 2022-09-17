/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:24:19 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/17 16:01:26 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../lib/libft/include/libft.h"
#include "../../lib/minilibx_opengl_20191021/mlx.h"

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

void	print_image(t_mlx *mlx, t_data *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			pixel_set(img, x, y, 0x0000FF00);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img->img, 0, 0);
	mlx_key_hook(mlx->win, key_hook, mlx);
	mlx_loop(mlx->mlx);
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
	print_image(mlx, img);
	map_free(map, 0);
	return (0);
}
