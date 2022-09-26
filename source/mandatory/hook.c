/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:20:41 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/25 19:17:24 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../lib/minilibx_opengl_20191021/mlx.h"
#include <stdlib.h>

int	key_hook(int key_code, t_fdf *fdf)
{
	if (key_code == 53)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		exit(0);
	}
	if (key_code >= 123 && key_code <= 126)
		move_map(key_code, fdf->map);
	else if ((key_code >= 0 && key_code <= 2)
		|| (key_code >= 12 && key_code <= 14))
		rotate_map(key_code, fdf->map);
	else if (key_code == 15)
		reset_map(fdf->map);
	print_image(fdf->map, fdf);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		fdf->map->gap += 0.5;
		print_image(fdf->map, fdf);
	}
	if (button == 5)
	{
		if (fdf->map->gap > 1)
			fdf->map->gap -= 0.5;
		print_image(fdf->map, fdf);
	}
	return (0);
}
