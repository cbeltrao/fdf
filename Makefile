# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/01 13:31:36 by cbeltrao          #+#    #+#              #
#    Updated: 2018/10/20 22:59:12 by cbeltrao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# the compiler
CC = gcc

# compiler flags:
CFLAGS = -Wall -Wextra -Werror

# name of executable
MAIN = main 

# header files
INCLUDES = -I ./minilibx_macos

# libraries path
LFLAGS = -L ./minilibx_macos

# define libraries to link into executable
LIBS = -lmlx

# define the C source files
SRCS = main.c libft/*.c gnl/*.c

# define the C objects files
OBJS = $(SRCS:.c=.o)

# define frameworks to link
FW1 = -framework OpenGL
FW2 = -framework AppKit

.PHONY: all clean fclean

all: $(MAIN)

$(MAIN): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS) $(FW1) $(FW2)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(MAIN)

re: fclean all
