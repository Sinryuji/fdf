# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 18:13:26 by hyeongki          #+#    #+#              #
#    Updated: 2022/09/11 20:01:32 by hyeongki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS_PATH = ./source/mandatory/
SRCS_NAME = fdf.c
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(SRCS:.c=.o)
BONUS_PATH = ./source/bonus/
BONUS_SRCS_NAME =
BONUS_SRCS = $(addprefix $(BONUS_PATH), $(BONUS_SRCS_NAME))
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
RM = rm -rf
AR = ar rcs
NAME = fdf
LIBFT_PATH = ./lib/libft/
LIBFT = ft
MLX_PATH = ./lib/minilibx_opengl_20191021/
MLX = mlx
FRAMEWORK = -framework OpenGL -framework Appkit

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) :  $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $^ -L$(MLX_PATH) -l$(MLX) -L$(LIBFT_PATH) -l$(LIBFT) $(FRAMEWORK) -o $@

clean :
	$(RM) $(OBJS) $(BONUS_OBJS) 
	make -C $(LIBFT_PATH) clean

fclean : clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean

re : fclean all

.PHONY :
	all clean fclean re
