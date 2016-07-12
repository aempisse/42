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

CC = gcc

CFLAGS = -Wall -Werror -Wextra

OBJ = ft_atoi.o ft_bzero.o ft_isalnum.o ft_isalpha.o
OBJ += ft_isascii.o ft_isdigit.o ft_isnumber.o ft_isprint.o 
OBJ += ft_isrange.o ft_isspace.o ft_iswhite.o ft_itoa.o 
OBJ += ft_max.o ft_memalloc.o ft_memccpy.o ft_memchr.o
OBJ += ft_memcmp.o ft_memcpy.o ft_memdel.o ft_memmove.o
OBJ += ft_memset.o ft_min.o ft_putchar.o ft_putchar_fd.o 
OBJ += ft_putendl.o ft_putendl_fd.o ft_putnbr.o ft_putnbr_fd.o
OBJ += ft_putstr.o ft_putstr_fd.o ft_strcat.o ft_strchr.o 
OBJ += ft_strclr.o ft_strcmp.o ft_strcpy.o ft_strdel.o 
OBJ += ft_strdup.o ft_strequ.o ft_striter.o ft_striteri.o 
OBJ += ft_strjoin.o ft_strlcat.o ft_strlen.o ft_strmap.o 
OBJ += ft_strmapi.o ft_strncat.o ft_strncmp.o ft_strncpy.o 
OBJ += ft_strnequ.o ft_strnew.o ft_strnstr.o ft_strrchr.o 
OBJ += ft_strsplit.o ft_strstr.o ft_strsub.o ft_strtrim.o 
OBJ += ft_tolower.o ft_toupper.o ft_lstadd.o ft_lstdel.o 
OBJ += ft_lstdelone.o ft_lstiter.o ft_lstmap.o ft_lstnew.o
OBJ += get_next_line.o ft_error.o
OBJ += ft_array_add.o ft_array_clr.o ft_array_ext.o ft_array_ini.o
OBJ += ft_array_kill.o ft_array_new.o
OBJ += ft_tab_add.o ft_tab_addn.o ft_tab_ext.o ft_tab_ini.o
OBJ += ft_tab_kill.o ft_tab_new.o
OBJ += ft_parse_int.o ft_parse_double.o ft_parse_space.o ft_parse_not.o

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " |        |"
	@echo " | libft  |"
	@echo " '--------'"

%.o: %.c
	@$(CC) $(FLAGS) -c $+

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
