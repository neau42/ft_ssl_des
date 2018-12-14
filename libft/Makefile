# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/27 07:13:00 by nboulaye          #+#    #+#              #
#    Updated: 2018/12/14 18:13:14 by nboulaye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCSPATH = ft_printf/
OPT_PATH = opt_parse_arg/
LIBFT_INCLUDES = includes

SR =	ft_printf.c\
		flags.c\
		read_arg.c\
		do_d.c\
		do_f.c\
		do_u.c\
		do_o.c\
		do_x.c\
		do_p.c\
		do_c.c\
		do_b.c\
		do_ls.c\
		do_s.c\
		do_not_specifier.c

SRCL =	ft_atoi.c\
		ft_atoh.c\
		ft_bzero.c\
		ft_capitaliz.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_isspace.c\
		ft_ishexdigit.c\
		ft_itoa_base_buffer.c\
		ft_memcpy.c\
		ft_memset.c\
		ft_strstr.c\
		ft_strcmp.c\
		ft_strncat.c\
		ft_strdup.c\
		ft_strnew.c\
		ft_strncmp.c\
		ft_strncpy.c\
		ft_memalloc.c\
		ft_strlen.c\
		ft_memmove.c\
		ft_strdel.c\
		ft_strjoin.c\
		ft_strjoin_free.c\
		ft_strcpy.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strrnchr.c\
		ft_strlast.c\
		ft_memchr.c\
		ft_strsplit.c\
		ft_strsplit_first.c\
		ft_toupper.c\
		ft_tolower.c

SRC =	$(SRCL)\
		$(addprefix $(SRCSPATH), $(SR))\
		$(addprefix $(OPT_PATH), $(OPT))\

WFLAGS = -Wall -Werror -Wextra 
# -fsanitize=address -g -ggdb

LFLAGS = -L libft/ -lft

CC = gcc

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o: %.c
	@$(CC) -c $(WFLAGS) -I $(LIBFT_INCLUDES)  $< -o $@

$(NAME) : $(OBJ)
	@echo 'compilation libft'
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo '- - - - - - ok'

clean :
	@echo "CLEAN LIBFT"
	@rm -rf $(OBJ)

fclean : clean
	@echo "FCLEAN LIBFT"
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
