/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:32:21 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/16 15:37:55 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../lib/libft/include/libft.h"
#include <fcntl.h>
#include <unistd.h>

int	get_map_size(t_map *map, int fd)
{
	char	*read;
	char	**split;
	int		save;

	save = -1;
	map->height = 0;
	while (1)
	{
		read = get_next_line(fd);
		if (!read)
			break ;
		split = ft_split(read, ' ');
		if (!split)
			return (-1);
		map->height++;
		map->width = 0;
		while (split[map->width])
			map->width++;
		if (save >= 0 && save != map->width)
			return (-2);
		save = map->width;
		free(read);
		ft_split_free(split);
	}
	return (0);
}

t_map	*init_map(char *map_str)
{
	int		fd;
	t_map	*map;
	int		ret;

	fd = open(map_str, O_RDONLY);
	if (fd < 0)
		ft_puterr("Map reading error\n");
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_puterr("Map malloc error\n");
	ret = get_map_size(map, fd);
	if (ret < 0)
	{
		free(map);
		close(fd);
		if (ret == -1)
			ft_puterr("Split error\n");
		else if (ret == -2)
			ft_puterr("The width of the map is inconsistent\n");
	}
	close(fd);
	map->map = (t_dot *)malloc(sizeof(t_dot) * map->height * map->width);
	return (map);
}

t_map	*read_map(char *map_str)
{
	char	*read;
	char	**split;
	t_map	*map;
	int		fd;

	map = init_map(map_str);
	fd = open(map_str, O_RDONLY);
	while (1)
	{
		read = get_next_line(fd);
		if (!read)
			break ;
		map->width++;
		split = ft_split(read, ' ');
		if (!split)
			ft_puterr("Split error\n");
		ft_split_free(split);
	}
	return (map);
}
