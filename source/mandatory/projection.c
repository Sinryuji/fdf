/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:39:14 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/23 20:45:07 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include <math.h>

void	map_move(int key_code, t_map *map)
{
	if (key_code == 123)
		map->x_move -= 5;
	else if (key_code == 124)
		map->x_move += 5;
	else if (key_code == 125)
		map->y_move += 5;
	else
		map->y_move -= 5;
}

void	isometric(double *x, double *y, double z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(M_PI / 6);
	*y = (prev_x + prev_y) * sin(M_PI / 6) - z;
}
