NAME = wolf3d

GCC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJ = obj/wolf3d.o obj/raycasting.o obj/hooks.o

LIBFT = -L./libft/ -lft

LIBMLX = -L./minilibx/ -lmlx_Linux -L/usr/lib/x86_64-linux-gnu/ -lXext -lX11 -lm

all: obj $(NAME)

$(NAME): $(OBJ)
#	@$(MAKE) -s -C ./libft/
	@$(GCC) $(CFLAGS) -o $@ $+ $(LIBFT) $(LIBMLX)
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " |        |"
	@echo " | wolf3d |"
	@echo " '--------'"

obj:
	@mkdir -p obj/

obj/%.o: %.c
	@$(GCC) -c $+ -o $@

$(LIBMLX): ./minilibx/libmlx.a
	@$(MAKE) -s -C ./minilibx/

clean:
	@rm -rf obj/
#	@$(MAKE) -s clean -C ./libft/
	@$(MAKE) -s clean -C ./minilibx/

fclean: clean
	@rm -f $(NAME)
#	@$(MAKE) -s fclean -C ./libft/

re: fclean all

.PHONY: all obj clean fclean norme re
