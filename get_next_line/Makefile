NAME = get_next_line.o

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	make re -C libft/
	gcc $(FLAGS) -o $@ -c get_next_line.c

clean:
	rm -f $(NAME)

re: clean all