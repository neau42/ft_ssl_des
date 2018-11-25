/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:18:48 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/25 10:22:01 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"

# define OPT_ERR  0x10000000
# define OPT_H    0x20000000
# define OPT_P    0x40000000
# define OPT_Q    0x80000000
# define OPT_R    0x1000000
# define OPT_S    0x2000000
# define OPT_FILE 0x4000000
#define CHKSUM_SIZE_MD5 (4 * sizeof(uint32_t))
#define CHKSUM_SIZE_SHA (8 * sizeof(uint32_t))

# define NULL_HASH 0x0
# define OPT_MD5 0x1
# define OPT_SHA256 0x2
# define GET_HASH 0x7

# define NULL_TYPE 0x0
# define FILE_TYPE 0x1
# define STRING_TYPE 0x2

# define SIZE_BUF 0x40
# define CHKSUM_SIZE 0x10

typedef struct	s_arg
{
	char			type;
	char			*str;
	struct s_arg	*next;
}				t_arg;

typedef	struct	s_read
{
	uint8_t		*buf;
	uint64_t	size;
	int			len;
	uint8_t		bsz;
	char		*file_name;

}				t_read;

typedef union	u_chksum
{
	uint32_t	md5[4];
	uint32_t	sha256[8];
}				t_chksum;

t_arg			*get_args(int ac, char **av, uint32_t *opts);
t_arg			*get_opts(char *str, char *str_next, uint32_t *opts,
								t_arg *arg);
t_arg			*init_arg(void);
void			short_usage(char *str);
void			long_usage(char *str);
void			rm_arg(t_arg *arg);

int				process_stdin(char *str, uint32_t opts);
int				process_file(char *file_name, uint32_t opts);
int				process_string(char *str, uint32_t opts);

void			init_chksum(t_chksum *sum, uint32_t opts);
void			init_chksum_n_read(t_chksum *sum, uint32_t opts, t_read *r,
										uint8_t *buf);

void			algo(void *buf, t_chksum *sum, uint32_t opts);
void			print_chksum(t_chksum *sum, char *file_name, uint32_t opts);

void			format_last_chunk(t_read *r, uint32_t opts, t_chksum *sum);

void			md5(const uint32_t *msg, t_chksum *r);
void			sha256(const uint32_t *msg, t_chksum *sum);

/*
** utils?
*/

uint64_t		endian_swap64(uint64_t x);
uint32_t		endian_swap32(uint32_t x);
uint32_t		r_rot(uint32_t n, unsigned int c);
void			print_memory_hex(void *data, size_t blk_size);

#endif
