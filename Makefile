# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbogar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/30 11:05:53 by sbogar            #+#    #+#              #
#    Updated: 2017/07/01 21:53:21 by sbogar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

INCLUDES = includes/fractol.h\
		   includes/events.h

FILES = main.c\
	   draw_window.c\
	   get_color.c\
	   events.c\
	   key_hook.c

FLAGS = -Wall -Werror -Wextra
LIBS = -L./mlx/ -lmlx -L./libft/ -lft
MLX = -framework OpenGL -framework Appkit

OBJS = $(addprefix objs/,$(FILES:.c=.o))
SRCS = $(addprefix srcs/,$(FILES))

.PHONY = all clean fclean re

all: $(NAME)

$(NAME): objs/ $(OBJS) libft/libft.a mlx/libmlx.a
	gcc  -o $(NAME) $(FLAGS) $(OBJS) $(LIBS) $(MLX)

libft/libft.a:
	make -C libft/

mlx/libmlx.a:
	make -C mlx/

objs/:
	@mkdir objs

objs/%.o: srcs/%.c
	@gcc -c $(FLAGS) $^ -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf objs

fclean: clean
	rm -f $(NAME)

re: fclean all
