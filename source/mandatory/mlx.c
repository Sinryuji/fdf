/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:43:43 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/17 15:46:43 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../lib/minilibx_opengl_20191021/mlx.h"

void	mlx_img_init(t_mlx *mlx, t_data *img)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Hello world!");
	img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
}
