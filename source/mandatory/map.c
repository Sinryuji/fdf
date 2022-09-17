/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:32:21 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/17 16:02:14 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../lib/libft/include/libft.h"
#include <fcntl.h>
#include <unistd.h>

void	map_free(t_map *map, int err_code)
{	
	if (map->map)
		free(map->map);
	free(map);
	if (err_code < 0)
		put_error(err_code);
}

int	get_map_size(t_map *map, int fd)
{
	char	*read;
	char	**split;
	int		save;

	save = -1;
	read = get_next_line(fd);
	while (read)
	{
		split = ft_split(read, ' ');
		if (!split)
			return (ERR_SPLIT);
		map->height++;
		map->width = 0;
		while (split[map->width])
			map->width++;
		if (*split[map->width - 1] == '\n')
			map->width--;
		if (save >= 0 && save != map->width)
			return (ERR_MAP_SIZE);
		save = map->width;
		free(read);
		ft_split_free(split);
		read = get_next_line(fd);
	}
	return (0);
}

static t_map	*init_map(char *file_addr)
{
	int		fd;
	t_map	*map;
	int		ret;

	fd = open(file_addr, O_RDONLY);
	if (fd < 0)
		put_error(ERR_OPEN);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		put_error(ERR_MALLOC);
	map->height = 0;
	ret = get_map_size(map, fd);
	close(fd);
	if (ret < 0 || map->width < 1 || map->height < 1)
		map_free(map, ret);
	map->map = (t_dot *)malloc(sizeof(t_dot) * map->height * map->width);
	if (!map->map)
		map_free(map, ERR_MALLOC);
	ft_memset(map->map, 0, sizeof(t_dot) * map->height * map->width);
	return (map);
}

static void	get_map_data(t_map *map, char **split)
{
	int			i;
	char		**data_str;
	static int	cnt = 0;

	i = 0;
	while (i < map->width)
	{
		data_str = ft_split(split[i], ',');
		if (!data_str)
		{
			map_free(map, 0);
			ft_split_free(split);
			put_error(ERR_SPLIT);
		}
		map->map[cnt].value = ft_atoi(data_str[0]);
		if (data_str[1])
			map->map[cnt].color = ft_atoi_hex(data_str[1]);
		i++;
		cnt++;
		ft_split_free(data_str);
	}
}

static void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width * map->height)
	{
		printf("%d,%d ", map->map[i].value, map->map[i].color);
		if ((i + 1) % map->width == 0)
			printf("\n");
		i++;
	}
}

t_map	*read_map(char *file_addr)
{
	char	*read;
	char	**split;
	t_map	*map;
	int		fd;

	map = init_map(file_addr);
	fd = open(file_addr, O_RDONLY);
	if (fd < 0)
	{
		map_free(map, 0);
		put_error(ERR_OPEN);
	}
	read = get_next_line(fd);
	while (read)
	{
		split = ft_split(read, ' ');
		if (!split)
			put_error(ERR_SPLIT);
		get_map_data(map, split);
		free(read);
		ft_split_free(split);
		read = get_next_line(fd);
	}
	print_map(map);
	return (map);
}
