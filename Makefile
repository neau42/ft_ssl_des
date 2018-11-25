# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/26 03:02:39 by no                #+#    #+#              #
#    Updated: 2018/11/25 22:48:04 by nboulaye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRC =	srcs/md5.c\
		srcs/algo.c\
		srcs/main.c\
		srcs/utils.c\
		srcs/usage.c\
		srcs/sha256.c\
		srcs/rm_data.c\
		srcs/get_args.c\
		srcs/get_opts.c\
		srcs/init_chksum.c\
		srcs/process_file.c\
		srcs/process_stdin.c\
		srcs/process_string.c

FLAGS = -Wall -Werror -Wextra

INC_PATH = incs/

LIBS = -lft
LIBFT_PATH = libft/
INC_LIBFT = libft/includes/

CC = gcc

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) -I $(INC_LIBFT) -I $(INC_PATH) $< -o $@

$(NAME): $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LIBFT_PATH) $(LIBS)

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(OBJ)
	rm -rf $(OBJ_CLIENT)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

test: 

re: fclean all

.PHONY: all clean fclean re
