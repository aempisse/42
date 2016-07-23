NAME = fractol

GCC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJ = obj/fractol.o obj/draw.o obj/hooks.o

LIBFT = -L./libft/ -lft

#LIBMLX = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
LIBMLX = -L./minilibx/ -lmlx -L/usr/lib/x86_64-linux-gnu/ -lXext -lX11 -lm

all: obj $(NAME)

$(NAME): $(OBJ)
#	@$(MAKE) -s -C ./libft/
	@$(GCC) $(CFLAGS) -o $@ $+ $(LIBFT) $(LIBMLX)
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " |        |"
	@echo " | fractol|"
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
