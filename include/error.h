/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:00:17 by hyeongki          #+#    #+#             */
/*   Updated: 2022/09/16 16:07:53 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_USAGE -1
# define ERR_OPEN -2
# define ERR_SPLIT -3
# define ERR_MAP_MALLOC -4
# define ERR_MAP_SIZE -5

/* error.c */
void	put_error(int err_code);

#endif
