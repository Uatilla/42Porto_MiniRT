# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/30 20:21:44 by uviana-a          #+#    #+#              #
#    Updated: 2024/08/29 17:00:51 by Jburlama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RESET 		=	\033[0m	
BLACK 		=	\033[1;30m
RED 		=	\033[1;31m
GREEN 		=	\033[1;32m
YELLOW 		=	\033[1;33m
BLUE 		=	\033[1;34m
PURPLE 		=	\033[1;35m
CYAN 		=	\033[1;36m
WHITE 		=	\033[1;37m

NAME		= minirt

# Commands
CC			= cc
RM			= rm -rf
GIT			= git

# Directories
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
LIBFT_DIR	=	./libraries/libft
MLX_DIR		=	./libraries/minilibx-linux
INC			=	includes
SUB_DIR		=	tuples input exit mlx ray canvas sphere window objects light \
				matrix matrix_transformations cylinder view camera render plane\
				patterns	
ALL_OBJS_DIR	= $(foreach dir, $(SUB_DIR), $(addprefix $(OBJS_DIR)/, $(dir)))

# Flags
CFLAGS		=	-Wall -Wextra -Werror -g #-pg
MLXFLAGS	=	-lmlx -lXext -lX11 -lm

# Files
SRCS		=	main.c \
				tuples/chk_tuples_typ.c tuples/creating_tuples.c tuples/operations_tuples.c tuples/basic_operations_tuples.c\
				input/input_checker.c \
				objects/parse_objs.c \
				light/light.c light/light_utils.c\
				ray/ray.c ray/intersections.c ray/sort_intersections.c \
				canvas/map.c \
				sphere/sphere.c \
				cylinder/cylinder.c \
				exit/exit_cleaner.c exit/clean_world.c \
				mlx/mlx.c \
				matrix/matrix_validations.c matrix/matrix_operations.c matrix/matrix_modifications.c matrix/matrix_mods_utils.c \
				matrix_transformations/matrix_transformations.c \
				matrix/mtx_temp.c \
				view/view_transformation.c \
				camera/camera.c	\
				render/render.c \
				plane/plane.c \
				patterns/patterns.c


OBJS		=	$(SRCS:%.c=$(OBJS_DIR)/%.o)
LIBFT		=	$(LIBFT_DIR)/libft.a
LIBMLX		=	$(MLX_DIR)/libmlx.a
MINIRT		=	$(INC)/minirt.h

# Rules
all: $(NAME)

$(NAME): $(MLX_DIR) $(OBJS) $(LIBMLX) $(LIBFT) $(MINIRT)
	@ $(CC)	$(CFLAGS) $(OBJS) -L$(MLX_DIR) $(MLXFLAGS) $(LIBFT) -o $(NAME)

$(OBJS_DIR):
	@ mkdir -p $(OBJS_DIR) $(ALL_OBJS_DIR)
	@ printf "Objects directories  	$(YELLOW)[OK]$(RESET)\n"

$(OBJS): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@ $(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@
	@ printf "Making binary files	$(YELLOW)[OK]$(RESET)\n"

$(LIBMLX): 
	@ printf "Making Minilibx		$(YELLOW)[OK]$(RESET)\n"
	@ $(MAKE)  -sC $(MLX_DIR) 2> /dev/null

$(LIBFT):
	@ printf "Making Libft		$(YELLOW)[OK]$(RESET)\n"
	@ $(MAKE)  -sC $(LIBFT_DIR)

$(MLX_DIR):
	@git clone --depth=1 https://github.com/42Paris/minilibx-linux.git 
	@make -sC minilibx-linux 2> /dev/null
	@mv minilibx-linux libraries/

clean:
	@ $(RM) $(OBJS_DIR) gmon.out analise.txt 2> /dev/null
	@ printf "cleaning MiniRT files	$(CYAN)[OK]$(RESET)\n"
	@ $(MAKE) $(MK_FLAG) clean -sC $(LIBFT_DIR)

fclean: clean
	@ $(RM) $(NAME)
	@ $(MAKE) $(MK_FLAG) fclean -sC $(LIBFT_DIR)
	@ printf "fclean			$(CYAN)[OK]$(RESET)\n"

re: fclean all

.SILENT:

.PHONY: all clean fclean re

gprof: $(NAME)
	 ./$(NAME)
	 gprof $(NAME) gmon.out > analise.txt
