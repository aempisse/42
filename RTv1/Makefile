NAME = rtv1

GCC = gcc

CFLAGS = -Wall -Wextra -Werror -g -O0

OBJ = obj/main.o obj/parser.o obj/object.o obj/raytracer.o obj/rotation.o obj/color.o obj/tools.o 
#obj/path.o 
OBJ += obj/sphere.o obj/plane.o obj/cylinder.o obj/cone.o

LIBFT = ./libft/libft.a

LIBMLX = -L./minilibx/ -lmlx_Linux -L/usr/lib/x86_64-linux-gnu/ -lXext -lX11 -lm
#LIBMLX = ./libmlx.a -framework OPENGL -framework Appkit

all: obj $(NAME)

$(NAME): $(OBJ)
#	@$(MAKE) -s -C ./libft/
	@$(GCC) $(CFLAGS) -o $@ $+ $(LIBFT) $(LIBMLX)
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " |        |"
	@echo " | RTv1   |"
	@echo " '--------'"

obj:
	@mkdir -p obj/

obj/%.o: src/%.c
	@$(GCC) -c $+ -o $@

clean:
	@rm -rf obj/
#	@$(MAKE) -s clean -C ./libft/

fclean: clean
	@rm -f $(NAME)
#	@$(MAKE) -s fclean -C ./libft/

re: fclean all

.PHONY: all obj clean fclean re
