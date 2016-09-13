# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aempisse <aempisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/08 19:10:02 by aempisse          #+#    #+#              #
#    Updated: 2015/12/06 20:00:19 by aempisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

GCC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJ = obj/fdf.o obj/map.o obj/draw.o obj/color.o 

LIBFT = -L./libft/ -lft

#LIBMLX = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
LIBMLX = -L./minilibx/ -lmlx_Linux -L/usr/lib/x86_64-linux-gnu/ -lXext -lX11 -lm

all: obj $(NAME)

obj:
	@mkdir -p obj/

$(NAME): $(OBJ)
	@$(MAKE) -s -C ./libft/
	@$(GCC) $(CFLAGS) -o $@ $+ $(LIBFT) $(LIBMLX)
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " |        |"
	@echo " | fdf    |"
	@echo " '--------'"

obj/%.o: %.c
	@$(GCC) -c $+ -o $@

$(LIBMLX): ./minilibx/libmlx.a
	@$(MAKE) -s -C ./minilibx/

clean:
	@rm -rf obj/
	@$(MAKE) -s clean -C ./libft/
	@$(MAKE) -s clean -C ./minilibx/

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s fclean -C ./libft/

re: fclean all

.PHONY: all obj clean fclean norme re
