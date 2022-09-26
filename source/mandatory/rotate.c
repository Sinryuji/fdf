/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:11:28 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/25 20:11:13 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include <math.h>

void	rotate_x(t_point *point, double alpha)
{
	int	prev_y;

	prev_y = point->y;
	point->y = prev_y * cos(alpha) + point->z * sin(alpha);
	point->z = -prev_y * sin(alpha) + point->z * cos(alpha);
}

void	rotate_y(t_point *point, double beta)
{
	int	prev_x;

	prev_x = point->x;
	point->x = prev_x * cos(beta) + point->z * sin(beta);
	point->z = -prev_x * sin(beta) + point->z * cos(beta);
}

void	rotate_z(t_point *point, double gamma)
{
	int	prev_x;
	int	prev_y;

	prev_x = point->x;
	prev_y = point->y;
	point->x = prev_x * cos(gamma) - prev_y * sin(gamma);
	point->y = prev_x * sin(gamma) + prev_y * cos(gamma);
}

void	rotate_map(int key_code, t_map *map)
{
	double	val;

	val = 0.1;
	if (key_code == 0)
		map->beta -= val;
	else if (key_code == 1)
		map->alpha += val;
	else if (key_code == 2)
		map->beta += val;
	else if (key_code == 13)
		map->alpha -= val;
	else if (key_code == 12)
		map->gamma -= val;
	else
		map->gamma += val;
}
