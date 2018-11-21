/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:18:48 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/21 00:57:51 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <fcntl.h>
     #include <math.h>
# include "libft.h"
# include "ft_printf.h"

# define OPT_ERR 0x1
# define OPT_H 0x2
# define OPT_P 0x4
# define OPT_Q 0x8
# define OPT_R 0x10
# define OPT_S 0x20
# define OPT_FILE 0x40

# define NULL_TYPE 0x0
# define FILE_TYPE 0x1
# define STRING_TYPE 0x2

# define SIZE_BUF 0x40 // 64o == 512b / 8
# define CHKSUM_SIZE 0x10 	// (16o = 128b / 8)

# define MD5_HASH 0x10000000
# define SHA256_HASH 0x20000000
# define NULL_HASH 0x40000000

typedef struct s_arg
{
	char			type;
	char			*str; // || file_name
	char			*file;
	struct s_arg	*next;
}				t_arg;

typedef	struct s_read
{
	int			len; // len = size % SIZE_BUF 
	uint64_t	size;
	uint8_t		buf[SIZE_BUF];	// (512 / 8)

}				t_read;

t_arg	*get_args(int ac, char **av, uint32_t *opts);
t_arg	*get_opts(char *str, char *str_next, uint32_t *opts, t_arg *arg);
t_arg	*init_arg(void);
void	short_usage(char *str);
void	long_usage(char *str);
void	rm_arg(t_arg *arg);


int		process_null(char *str, uint32_t opts);
int		process_file(char *file_name, uint32_t opts);
int		process_string(char *str, uint32_t opts);

/*
** utils?
*/
uint64_t    leftrotate (uint64_t x, int offset);
uint64_t    endian_swap64(uint64_t x);
void        print_memory_hex(void *data, size_t blk_size);



#endif
