# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aempisse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/12 08:22:50 by aempisse          #+#    #+#              #
#    Updated: 2015/11/24 18:23:03 by aempisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

CFLAGS = -Wall -Werror -Wextra

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c
SRC += ft_isascii.c ft_isdigit.c ft_isnumber.c ft_isprint.c 
SRC += ft_isrange.c ft_isspace.c ft_iswhite.c ft_itoa.c 
SRC += ft_max.c ft_memalloc.c ft_memccpy.c ft_memchr.c
SRC += ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c
SRC += ft_memset.c ft_min.c ft_putchar.c ft_putchar_fd.c 
SRC += ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c
SRC += ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c 
SRC += ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c 
SRC += ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c 
SRC += ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c 
SRC += ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c 
SRC += ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c 
SRC += ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c 
SRC += ft_tolower.c ft_toupper.c ft_lstadd.c ft_lstdel.c 
SRC += ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c
SRC += get_next_line.c ft_error.c
SRC += ft_arrayadd.c ft_arrayclr.c ft_arrayext.c ft_arrayini.c
SRC += ft_arraykil.c ft_arraynew.c
SRC += ft_tabadd.c ft_tabaddn.c ft_tabext.c ft_tabini.c
SRC += ft_tabkil.c ft_tabnew.c
SRC += ft_parseint.c ft_parsedouble.c ft_parsespace.c ft_parsenot.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " |        |"
	@echo " | libft.a|"
	@echo " '--------'"

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " | .o     |"
	@echo " | deleted|"
	@echo " '--------'"

fclean: clean
	@rm -f $(NAME)
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " | libft.a|"
	@echo " | deleted|"
	@echo " '--------'"

re: fclean all

.PHONY: all clean fclean re
