NAME = rt

GCC = gcc

CFLAGS = -Wall -Wextra -Werror -g -Wuninitialized -O0 -D_REENTRANT

OBJ = obj/main.o obj/tools.o obj/matrix.o obj/object.o obj/add_pars_value.o
OBJ += obj/init_object.o obj/test_pars_tools.o obj/check_files.o
OBJ += obj/check_color_obj.o obj/check_balise_line.o obj/add_param.o obj/pars_space_value.o
OBJ += obj/test_pars_tools2.o obj/color.o obj/plane.o obj/sphere.o
OBJ += obj/cone.o obj/cylinder.o
OBJ += obj/raytracer.o obj/rotation.o obj/render.o obj/intersect.o obj/cut.o
OBJ += obj/reflexion.o obj/refraction.o obj/hooks.o obj/pars_head_value.o
OBJ += obj/intersect_tools.o obj/math.o obj/vector.o obj/multi_threading.o obj/init_menu.o obj/ft_new_image.o
OBJ += obj/render_menu.o obj/draw_menu.o obj/draw_tools.o obj/save_img.o obj/parse_error.o
OBJ += obj/texture.o

LIBFT = ./libft/libft.a

# LIBMLX = -L./minilibx/ -lmlx_Linux -L/usr/lib/x86_64-linux-gnu/ -lXext -lX11 -lm -lpthread
LIBMLX = ./libmlx.a -framework OPENGL -framework Appkit -lpthread

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
#	@$(MAKE) -s clean -C ./libft/

fclean: clean
	@rm -f $(NAME)
#	@$(MAKE) -s fclean -C ./libft/

re: fclean all

.PHONY: all obj clean fclean re
