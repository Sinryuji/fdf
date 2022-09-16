/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:03:01 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/16 16:07:16 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/error.h"
#include "../../lib/libft/include/libft.h"

void	put_error(int err_code)
{
	if (err_code == -1)
		ft_puterr("Invalid number of factors.\nUsage: ./fdf [fdf file]\n");
	if (err_code == -2)
		ft_puterr("File open error\n");
	if (err_code == -3)
		ft_puterr("Split error\n");
	if (err_code == -4)
		ft_puterr("Map malloc error\n");
	if (err_code == -5)
		ft_puterr("Map size error\n");
}
