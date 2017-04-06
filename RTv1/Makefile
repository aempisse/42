NAME = rtv1

GCC = gcc

CFLAGS = -Wall -Wextra -Werror -g -O0

OBJ = obj/main.o obj/raytracer.o obj/tools.o obj/sphere.o obj/check_pars_cone.o obj/init_light_obj.o obj/plane.o obj/path.o obj/check_files.o obj/check_pars_sphere.o obj/test_pars_tools.o obj/check_pars_plane.o obj/check_pars_cylinder.o obj/check_pars_light.o obj/init_object.o obj/add_pars_value.o obj/check_pars_camera.o

LIBFT = ./libft/libft.a

#LIBMLX = -L./minilibx/ -lmlx_Linux -L/usr/lib/x86_64-linux-gnu/ -lXext -lX11 -lm
LIBMLX = ./libmlx.a -framework OPENGL -framework Appkit

all: obj $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -s -C ./libft/
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
	@$(MAKE) -s clean -C ./libft/

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s fclean -C ./libft/

re: fclean all

.PHONY: all obj clean fclean re
