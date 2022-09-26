/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:24:19 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/26 20:27:00 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include "../../lib/minilibx_opengl_20191021/mlx.h"
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	t_fdf	*fdf;

	if (argc != 2)
		put_error(ERR_USAGE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		put_error(ERR_OPEN);
	fdf = fdf_init();
	fdf->map = read_map(fd);
	print_image(fdf->map, fdf);
	mlx_hook(fdf->win, 2, 0, key_hook, fdf);
	mlx_mouse_hook(fdf->win, mouse_hook, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
