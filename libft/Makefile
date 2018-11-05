# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/01 09:36:52 by cbeltrao          #+#    #+#              #
#    Updated: 2018/10/29 16:06:23 by cbeltrao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
SRC_DIR=./

FX=\
   ft_memset\
   ft_bzero\
   ft_memcpy\
   ft_memccpy\
   ft_memmove\
   ft_memchr\
   ft_memcmp\
   ft_strlen\
   ft_strdup\
   ft_strcpy\
   ft_strncpy\
   ft_strcat\
   ft_strncat\
   ft_strlcat\
   ft_strchr\
   ft_strrchr\
   ft_strstr\
   ft_strnstr\
   ft_strcmp\
   ft_strncmp\
   ft_strrev\
   ft_atoi\
   ft_isalpha\
   ft_isdigit\
   ft_isalnum\
   ft_isascii\
   ft_isprint\
   ft_isspace\
   ft_toupper\
   ft_tolower\
   ft_memalloc\
   ft_memrealloc\
   ft_memdel\
   ft_strnew\
   ft_strdel\
   ft_strclr\
   ft_striter\
   ft_striteri\
   ft_strmap\
   ft_strmapi\
   ft_strequ\
   ft_strnequ\
   ft_strsub\
   ft_strjoin\
   ft_strtrim\
   ft_strsplit\
   ft_itoa\
   ft_putchar\
   ft_putstr\
   ft_putendl\
   ft_putnbr\
   ft_putchar_fd\
   ft_putstr_fd\
   ft_putendl_fd\
   ft_putnbr_fd\
   get_next_line

OPTIONS=-I./includes
FLAGS=-Wall -Wextra -Werror

CFILES=$(patsubst %, $(SRC_DIR)%.c, $(FX))
OFILES=$(patsubst %, %.o, $(FX))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	@gcc $(OPTIONS) $(FLAGS) -c $(CFILES)
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OFILES)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
