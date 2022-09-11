/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:24:32 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/11 21:35:20 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/minilibx_opengl_20191021/mlx.h"
# include "../lib/libft/include/libft.h"

typedef struct s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx 
{
	void	*mlx;
	void	*win;	
}	t_mlx;

#endif
