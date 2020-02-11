# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 21:50:26 by yinzhang          #+#    #+#              #
#    Updated: 2020/02/10 21:50:27 by yinzhang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_fractol

CFLAGS = -Wall -Werror -Wextra

INCLUDE = fractol.h

MINILIBX = ./minilibx_macos/

FILES = main.c mandelbrot.c keys.c keys_2.c julia.c helper2.c helper.c burningship.c

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME)
	@make re -C $(MINILIBX)
	@gcc $(CFLAGS) -L $(MINILIBX) -I $(MINILIBX) -lmlx -framework OpenGL -framework Appkit $(FILES) -o $(NAME)

clean:
	@rm -f (OBJ)

fclean:

re: fclean all
