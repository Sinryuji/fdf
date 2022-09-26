/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:39:14 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/24 19:34:32 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include <math.h>

void	reset_map(t_map *map)
{
	map->x_move = 0;
	map->y_move = 0;
	map->alpha = 0;
	map->beta = 0;
	map->gamma = 0;
}

void	move_map(int key_code, t_map *map)
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

void	isometric(t_point *point)
{
	double	prev_x;
	double	prev_y;

	prev_x = point->x;
	prev_y = point->y;
	point->x = (prev_x - prev_y) * cos(M_PI / 6);
	point->y = (prev_x + prev_y) * sin(M_PI / 6) - point->z;
}
