/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:43:43 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/19 15:24:02 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../lib/minilibx_opengl_20191021/mlx.h"
#include <stdlib.h>

t_fdf	*fdf_init(void)
{
	t_fdf	*new;

	new = (t_fdf *)malloc(sizeof(t_fdf));
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, WIDTH, HEIGHT, "FDF!");
	new->img = mlx_new_image(new->mlx, WIDTH, HEIGHT);
	new->addr = mlx_get_data_addr(new->img, &new->bits_per_pixel, \
	&new->line_length, &new->endian);
	return (new);
}
