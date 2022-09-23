# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 18:13:26 by hyeongki          #+#    #+#              #
#    Updated: 2022/09/23 20:40:43 by hyeongki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS_PATH = ./source/mandatory/
SRCS_NAME = main.c map.c error.c mlx.c projection.c stack.c hook.c print.c
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

# Colors
GREEN = \x1b[32m
RED = \x1b[31m
RESET = \x1b[0m

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

all : $(NAME)

$(NAME) :  $(OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $^ -L$(MLX_PATH) -l$(MLX) -L$(LIBFT_PATH) -l$(LIBFT) $(FRAMEWORK) -o $@
	@echo "$@: $(GREEN)$@ was created$(RESET)"

clean :
	@$(RM) $(OBJS) $(BONUS_OBJS) 
	@make -C $(LIBFT_PATH) clean
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean : clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re : fclean all

.PHONY :
	all clean fclean re
