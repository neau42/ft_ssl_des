/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:18:48 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/19 03:47:38 by nboulaye         ###   ########.fr       */
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
# define OPT_R     0x1000000
# define OPT_S     0x2000000
# define OPT_FILE  0x4000000
# define OPT_DD    0x8000000

# define OPT_D      0x100000
# define OPT_E      0x200000
# define OPT_I      0x400000
# define OPT_O      0x800000

# define OPT_A       0x80000
# define OPT_K       0x40000
# define OPT_V       0x20000
# define OPT_PP      0x10000

# define CHKSUM_SIZE_MD5 (4 * sizeof(uint32_t))
# define CHKSUM_SIZE_SHA (8 * sizeof(uint32_t))

# define NULL_HASH  0x0
# define OPT_MD5    0x1
# define OPT_SHA256 0x2
# define OPT_BASE64 0x3
# define OPT_DES    0x4
# define OPT_ECB    0x5
# define OPT_CBC    0x6

# define OPT_CFB    0x7
# define OPT_CTR    0x9
# define OPT_PCBC   0xa

# define GET_HASH   0xF

# define NULL_TYPE   0x0
# define FILE_TYPE   0x1
# define STRING_TYPE 0x2
# define BASE64_TYPE 0x3
# define DES_TYPE    0x4

# define MD_BUF_SIZE      64
# define B64_ENC_BUF_SIZE 48
# define B64_DEC_BUF_SIZE 64

static uint8_t g_ip[] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20,
	12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49,
	41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21,
	13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

static uint8_t g_e_bit_sel[] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10,
	11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23,
	24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

static uint8_t g_s[8][64] = {
	{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 0, 15, 7, 4, 14, 2,
		13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9,
		7, 3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
	{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 3, 13, 4, 7, 15, 2,
		8, 14, 12, 0, 1, 10, 6, 9, 11, 5, 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12,
		6, 9, 3, 2, 15, 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
	{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 13, 7, 0, 9, 3, 4, 6,
		10, 2, 8, 5, 14, 12, 11, 15, 1, 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12,
		5, 10, 14, 7, 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
	{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 13, 8, 11, 5, 6, 15,
		0, 3, 4, 7, 2, 12, 1, 10, 14, 9, 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3,
		14, 5, 2, 8, 4, 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
	{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 14, 11, 2, 12, 4, 7,
		13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12,
		5, 6, 3, 0, 14, 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
	{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 10, 15, 4, 2, 7, 12,
		9, 5, 6, 1, 13, 14, 0, 11, 3, 8, 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10,
		1, 13, 11, 6, 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
	{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 13, 0, 11, 7, 4, 9,
		1, 10, 14, 3, 5, 12, 2, 15, 8, 6, 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6,
		8, 0, 5, 9, 2, 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
	{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 1, 15, 13, 8, 10, 3,
		7, 4, 12, 5, 6, 11, 0, 14, 9, 2, 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10,
		13, 15, 3, 5, 8, 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

static uint8_t g_p[] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31,
	10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};

static uint8_t g_ip_rev[] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55,
	23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10,
	50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};

static char g_b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
"0123456789+/";

typedef struct	s_base64
{
	char			type;
	char			*input;
	char			*output;
	int				fd_i;
	int				fd_o;
}				t_base64;

typedef struct	s_des
{
	char			type;
	char			*input;
	char			*output;
	int				fd_i;
	int				fd_o;
	char			*key;
	char			*pass;
	char			*salt;
	char			*vector;
	uint64_t		key_val;
	uint64_t		vec_val;
	uint64_t		salt_val;
	uint64_t		buf;
}				t_des;

typedef struct	s_base
{
	char			type;
}				t_base;

typedef struct	s_arg
{
	char			type;
	char			*str;
	t_base			*base;
	struct s_arg	*next;
}				t_arg;

typedef	struct	s_read
{
	uint8_t			*buf;
	uint64_t		size;
	int				len;
	uint8_t			bsz;
	char			*file_name;

}				t_read;

typedef union	u_chksum
{
	int				err;
	uint32_t		md5[4];
	uint32_t		sha256[8];
}				t_chksum;

t_arg			*get_args(int ac, char **av, uint32_t *opts);
t_arg			*get_md_option(char *str, char *str_next, uint32_t *opts,
						t_arg *arg);
void			get_base64_option(char *str, char *str_next, uint32_t *opts,
						t_base *base);
void			get_des_option(char *str, char *str_next, uint32_t *opts,
						t_base *base);
void			ft_opt_err(uint32_t *opts, char *str);
uint32_t		get_command(char *str, uint32_t *opts);
t_arg			*arg_error(uint32_t *opts, char *str, t_arg *first);

t_arg			*init_arg(void);
void			short_usage(char *str);
void			long_usage(char *str);
void			rm_arg(t_arg *arg);
t_chksum		process_stdin(t_arg *arg, uint32_t opts, uint8_t print);
t_chksum		process_file(t_arg *arg, uint32_t opts, uint8_t print);
t_chksum		process_string(t_arg *arg, uint32_t opts, uint8_t print);
int				get_input_file(char *file_name);
int				get_output_file(char *file_name);
t_chksum		process_des(t_arg *arg, uint32_t opts, uint8_t print);
t_chksum		process_string_custom(t_arg *arg, uint32_t opts, int len);
t_chksum		process_base64(t_arg *arg, uint32_t opts, uint8_t print);
void			init_chksum_n_read(t_chksum *sum, uint32_t opts, t_read *r,
										uint8_t *buf);
void			algo(void *buf, t_chksum *sum, uint32_t opts);
void			print_chksum(t_chksum *sum, char *file_name, uint32_t opts);
void			format_last_chunk(t_read *r, uint32_t opts, t_chksum *sum);
void			md5(const uint32_t *msg, t_chksum *sum, uint32_t opts);
void			sha256(const uint32_t *msg, t_chksum *sum, uint32_t opts);
void			b64_encode(t_base64 *base);
void			b64_decode(t_base64 *base);
void			b64_encode_buffer(t_base64 *base, char *buf, int len);

uint64_t		ft_des_rounds(uint64_t msg, uint64_t *k);

uint64_t		endian_swap64(uint64_t x);
uint32_t		endian_swap32(uint32_t x);
uint32_t		r_rot(uint32_t n, unsigned int c);
uint32_t		l_rot(uint32_t n, unsigned int c);
uint32_t		l_rot28(uint32_t n, unsigned int c);
uint64_t		ft_f(uint32_t right, uint64_t key);
uint64_t		permut_bits(uint64_t original_len, uint64_t final_len,
								uint64_t value, uint8_t *permut_tab);
uint64_t		unpermut_bits(uint64_t len, uint64_t value,
								uint8_t *permut_tab);
uint64_t		str_to_uint64(unsigned char *str);

int				get_magic_salt(int fd, uint64_t *salt_val, uint32_t opts,
								uint64_t *buf_save);
void			des_close_n_free(t_des *des);
int				valid_params(t_des *des, uint32_t opts);

void			print_memory_hex(void *data, size_t blk_size);
void			des_algo(const uint32_t *buf, t_chksum *sum, uint32_t opts);
void			des_algo_decrypt(t_des *des, uint32_t opts, uint64_t *buf);

uint64_t		des_decode(t_des *des, uint64_t msg, uint64_t *k,
														uint32_t opts);

void			decode_des_msg(t_des *des, uint64_t *msg, int size,
											uint32_t opts);
uint64_t		ft_des_rounds_rev(uint64_t msg, uint64_t *k);

uint64_t		*des_gen_keytab(uint64_t key);
void			b64_decode_str(char *buf_in, char *buf_out, size_t size);
int				read_trim(int fd, char *buf, size_t size);
void			process_des_chunk(t_des *des, uint64_t *k, uint64_t *final_buf,
																uint32_t opts);

#endif
