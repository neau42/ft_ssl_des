/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 04:00:08 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/09 18:40:47 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint8_t g_pc1[] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31,
	23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28,
	20, 12, 4};

static uint8_t g_pc2[] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12,
	4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33,
	48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

static uint8_t g_ip[] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20,
	12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49,
	41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21,
	13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

static uint8_t g_e_bit_sel[] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10,
	11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23,
	24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

static uint8_t g_S[8][64] = {
	{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 0, 15, 7, 4, 14, 2,
	13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9,
	7, 3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
	{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 3, 13, 4, 7, 15, 2,
	8, 14, 12, 0, 1, 10, 6, 9, 11, 5, 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6,
	9, 3, 2, 15, 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
	{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 13, 7, 0, 9, 3, 4, 6,
	10, 2, 8, 5, 14, 12, 11, 15, 1, 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5,
	10, 14, 7, 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
	{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 13, 8, 11, 5, 6, 15,
	0, 3, 4, 7, 2, 12, 1, 10, 14, 9, 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14,
	5, 2, 8, 4, 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
	{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 14, 11, 2, 12, 4, 7,
	13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6,
	3, 0, 14, 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
	{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 10, 15, 4, 2, 7, 12,
	9, 5, 6, 1, 13, 14, 0, 11, 3, 8, 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1,
	13, 11, 6, 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
	{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 13, 0, 11, 7, 4, 9,
	1, 10, 14, 3, 5, 12, 2, 15, 8, 6, 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8,
	0, 5, 9, 2, 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
	{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 1, 15, 13, 8, 10, 3,
	7, 4, 12, 5, 6, 11, 0, 14, 9, 2, 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13,
	15, 3, 5, 8, 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11} };

static uint8_t g_p[] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31,
	10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};

static uint8_t g_ip_rev[] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55,
	23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10,
	50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};


uint64_t	permut_bits(uint64_t original_len, uint64_t final_len,
								uint64_t value, uint8_t *permut_tab)
{
	int			i;
	uint64_t	ret;

	i = -1;
	ret = 0;
	while (++i < (int)final_len)
		ret |= (((value & (1UL << (original_len - permut_tab[i])))
				>> (original_len - permut_tab[i])) << ((final_len - 1) - i));
	return (ret);
}

void		gen_keytab(uint64_t key, uint64_t *k)
{
	int			i;
	uint64_t	tmp;
	uint32_t	c0;
	uint32_t	d0;

	tmp = permut_bits(64, 56, key, g_pc1);
	c0 = 0xFFFFFFF & (tmp >> 28);
	d0 = 0xFFFFFFF & tmp;
	i = 0;
	while (++i < 17)
	{
		c0 = l_rot28(c0, (i < 3 || i == 9 || i == 16) ? 1 : 2);
		d0 = l_rot28(d0, (i < 3 || i == 9 || i == 16) ? 1 : 2);
		k[i - 1] = permut_bits(56, 48, d0 + ((uint64_t)c0 << 28), g_pc2);
	}
	i = 0;
}

uint64_t 	ft_f(uint32_t right, uint64_t key)
{
	int			i;
	uint8_t		b[8];
	uint32_t	result;

	key = key ^ permut_bits(32, 48, right, g_e_bit_sel);
	i = 0;
	while (++i <= 8)
	{
		b[8 - i] = key & 0x3F;
		key >>= 6;
	}
	result = 0;
	i = -1;
	while (++i < 8)
		result |= ((g_S[i][((b[i] & 0x1E) >> 1) + 16 * (((b[i] & 0x20) >> 4)
					+ (b[i] & 0x1))]) << (28 - (i * 4)));
	return (permut_bits(32, 32, result, g_p));
}

uint64_t	ft_des_rounds(uint64_t msg, uint64_t *k)
{
	uint32_t	left;
	uint32_t	right;
	uint32_t	tmp_left;
	int			i;

	right = msg;
	left = (msg >> 32);
	i = 0;
	while (++i < 17)
	{
		tmp_left = left;
		left = right;
		right = tmp_left ^ ft_f(right, k[i - 1]);
	}
	return (left + ((uint64_t)right << 32));
}

void	process_des_chunk(uint64_t buf, uint64_t *k, uint64_t *final_buf)
{
	uint64_t	result;

	buf = endian_swap64(buf);
	result = ft_des_rounds(permut_bits(64, 64, buf, g_ip), k);
	result = permut_bits(64, 64, result, g_ip_rev);
	result = endian_swap64(result);
	ft_memcpy((uint8_t *)final_buf, (void *)&result, 8);
}

void des_print(t_des *des, uint64_t *final_buf, int *i, uint32_t opts)
{
	if (*i == 6)
	{
		(opts & OPT_A) ?
		b64_encode_buffer((t_base64 *)des, (char *)final_buf, 48)
		: write(des->fd_o, final_buf, 48);
		*i = 0;
	}
}


void read_loop( t_des *des, uint64_t *k, uint64_t *final_buf, uint32_t opts)
{
	uint64_t	buf;
	int			i;
	int			read_size;
	uint64_t	padding;
	uint64_t	padding_nb;

	i = 0;
	if (des->pass)
		i = 2;
	buf = 0;
	padding = 100;
	while ((read_size = read(des->fd_i, &buf, (sizeof(uint64_t)))) > 0)
	{
		if (read_size < (int)(sizeof(uint64_t)))
		{
			padding = (int)(sizeof(uint64_t)) - read_size;
			padding_nb = (int)(sizeof(uint64_t)) - read_size;
			while (padding_nb-- >0)
				buf |= (padding << (uint64_t)(64 - (padding_nb + 1) * 8));
		}
		else
			padding = 100;
		process_des_chunk(buf, k, &final_buf[i]);
		i++;
		des_print(des, final_buf, &i, opts);
		buf = 0;
	}
	if (padding == 100)
	{
		buf |= 0x0808080808080808;
		process_des_chunk(buf, k, &final_buf[i]);
		i++;
	}
	if (i)
		(opts & OPT_A) ? b64_encode_buffer((t_base64 *)des, (char *)final_buf, i * 8) : write(des->fd_o, final_buf, i * 8);
}

void		des_algo(const uint32_t *ptr, t_chksum *sum, uint32_t opts)
{
	uint64_t	k[16];
	t_des		*des;
	uint64_t	final_buf[6] = {0};
	uint64_t	test;

	(void)sum;
	des = (t_des *)ptr;
	if (des->pass)
	{
		ft_memcpy((uint8_t *)&final_buf[0], "Salted__", 8);
		test = endian_swap64((uint64_t)des->salt_val);
		ft_memcpy((uint8_t *)&final_buf[1], &test, 8);
	}
	gen_keytab(des->key_val, k);
	if (opts & OPT_PP)
	ft_fdprintf(2, "Key : %016.16llX\nVect: %016.16llX\nSalt: %016.16llX\nPass: %s\n",
		(des->key_val), (des->vec_val), (des->salt_val), des->pass);
	read_loop(des, k, final_buf, opts);
}
