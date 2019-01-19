# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/26 03:02:39 by no                #+#    #+#              #
#    Updated: 2019/01/19 00:43:52 by nboulaye         ###   ########.fr        #
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
		srcs/get_io_file.c\
		srcs/init_chksum.c\
		srcs/des_algo.c\
		srcs/process_file.c\
		srcs/process_stdin.c\
		srcs/base64_encode.c\
		srcs/base64_decode.c\
		srcs/process_base64.c\
		srcs/des_gen_keytab.c\
		srcs/process_des.c\
		srcs/get_command.c\
		srcs/base64_decode_str.c\
		srcs/get_md_option.c\
		srcs/read_trim.c\
		srcs/des_free.c\
		srcs/decode_des_msg.c\
		srcs/valid_des_params.c\
		srcs/des_algo_decrypt.c\
		srcs/process_des_chunk.c\
		srcs/permut_bits_n_endian_swap.c\
		srcs/get_magic_salt.c\
		srcs/process_string.c

FLAGS = -Wall -Werror -Wextra
# -fsanitize=address -g -ggdb

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

re: fclean all

.PHONY: all clean fclean re
