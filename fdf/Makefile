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

SRC = fdf.c map.c draw.c color.c misc.c

OBJ = $(SRC:%.c=obj/%.o) 

LIBFT = -L./libft/ -lft

#LIBMLX = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
LIBMLX = -L./minilibx/ -lmlx -L/usr/lib/x86_64-linux-gnu/ -lXext -lX11 -lm

GCC = gcc

CFLAGS = -Wall -Wextra -Werror

all: obj $(NAME)

$(NAME): $(OBJ)
#	@$(MAKE) -C ./libft/ -f Makefile
	@$(GCC) $(CFLAGS) -o $@ $(OBJ) $(LIBFT) $(LIBMLX) 
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " |        |"
	@echo " | fdf    |"
	@echo " '--------'"

obj:
	@mkdir -p obj/

obj/%.o: %.c
	@$(GCC) -c $< -o $@ 

$(LIBMLX): ./minilibx/libmlx.a
	@$(MAKE) -C ./minilibx/ -f Makefile
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " |        |"
	@echo " | libmlx |"
	@echo " '--------'" 

clean:
	@rm -rf obj/
#	@$(MAKE) clean -C ./libft/ -f Makefile
	@$(MAKE) clean -C ./minilibx/ -f Makefile
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " | mlx*.o |"
	@echo " | deleted|"
	@echo " '--------'" 


fclean: clean
	@rm -f $(NAME)
#	@$(MAKE) fclean -C ./libft/ -f Makefile

norme:
	norminette $(SRC)

re: fclean all

.PHONY: all obj clean fclean norme re
