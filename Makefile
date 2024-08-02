# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/30 20:21:44 by uviana-a          #+#    #+#              #
#    Updated: 2024/07/30 20:21:45 by uviana-a         ###   ########.fr        #
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
SUB_DIR		=	tuples input exit
ALL_OBJS_DIR	= $(foreach dir, $(SUB_DIR), $(addprefix $(OBJS_DIR)/, $(dir)))

# Flags
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
MLXFLAGS	=	-lmlx -lXext -lX11 -lm

# Files
SRCS		=	main.c \
				tuples/chk_tuples_typ.c tuples/creating_tuples.c \
				input/input_checker.c \
				exit/exit_cleaner.c
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
	@ $(MAKE)  -sC $(MLX_DIR)

$(LIBFT):
	@ printf "Making Libft		$(YELLOW)[OK]$(RESET)\n"
	@ $(MAKE)  -sC $(LIBFT_DIR)

$(MLX_DIR):
	@git clone --depth=1 https://github.com/42Paris/minilibx-linux.git 
	@make -sC minilibx-linux
	@mv minilibx-linux libraries/

clean:
	@ $(RM) $(OBJS_DIR)
	@ printf "cleaning MiniRT files	$(CYAN)[OK]$(RESET)\n"
	@ $(MAKE) $(MK_FLAG) clean -sC $(MLX_DIR)
	@ $(MAKE) $(MK_FLAG) clean -sC $(LIBFT_DIR)

fclean: clean
	@ $(RM) $(NAME)
	@ $(MAKE) $(MK_FLAG) fclean -sC $(LIBFT_DIR)
	@ printf "fclean			$(CYAN)[OK]$(RESET)\n"

re: fclean all

.SILENT:

.PHONY: all clean fclean re
