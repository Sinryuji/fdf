/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:48:58 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/26 20:34:28 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include <stdlib.h>

void	data_to_arr(t_map *map, t_data *data)
{
	int		i;
	t_data	*tmp;

	i = map->width * map->height;
	map->z_arr = (int *)malloc(sizeof(int) * i);
	map->color_arr = (int *)malloc(sizeof(int ) * i);
	if (!map->z_arr || !map->color_arr)
		put_error(ERR_MALLOC);
	while (i--)
	{
		map->z_arr[i] = data->z;
		map->color_arr[i] = data->color;
		tmp = data;
		data = data->next;
		free(tmp);
	}
}

void	push(t_data **data, int z, int color)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		put_error(ERR_MALLOC);
	new->z = z;
	new->color = color;
	if (*data)
		new->next = *data;
	else
		new->next = NULL;
	*data = new;
}
