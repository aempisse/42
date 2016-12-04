NAME = rtv1

GCC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJ = obj/main.o obj/parser.o

LIBFT = -L./libft/ -lft

all: obj $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -s -C ./libft/
	@$(GCC) $(CFLAGS) -o $@ $+ $(LIBFT)
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
