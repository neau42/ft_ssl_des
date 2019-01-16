/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 04:00:08 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/16 15:14:38 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	ft_f(uint32_t right, uint64_t key)
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

void		process_des_chunk(uint64_t buf, uint64_t *k, uint64_t *final_buf)
{
	uint64_t	result;

	buf = endian_swap64(buf);
	result = ft_des_rounds(permut_bits(64, 64, buf, g_ip), k);
	result = endian_swap64(permut_bits(64, 64, result, g_ip_rev));
	ft_memcpy((uint8_t *)final_buf, (void *)&result, 8);
}

void		des_print(t_des *des, uint64_t *final_buf, int *i, uint32_t opts)
{
	if (*i == 6)
	{
		(opts & OPT_A) ?
		b64_encode_buffer((t_base64 *)des, (char *)final_buf, 48)
		: write(des->fd_o, final_buf, 48);
		*i = 0;
	}
}

uint64_t	add_padding(int read_size, uint64_t *buf)
{
	uint64_t padding;
	uint64_t padding_nb;

	padding = (int)(sizeof(uint64_t)) - read_size;
	padding_nb = (int)(sizeof(uint64_t)) - read_size;
	while (padding_nb-- > 0)
		*buf |= (padding << (uint64_t)(64 - (padding_nb + 1) * 8));
	return (padding);
}

void		des_last_chunk(uint64_t buf, uint64_t *final_buf, uint64_t *k,
																	int *i)
{
	buf |= 0x0808080808080808;
	process_des_chunk(buf, k, &final_buf[(*i)]);
	(*i)++;
}

void		read_loop(t_des *des, uint64_t *k, uint64_t *final_buf,
														uint32_t opts)
{
	uint64_t	buf;
	int			i;
	int			read_size;
	uint64_t	padding;

	i = (des->pass) ? 2 : 0;
	buf = 0;
	padding = 100;
	while ((read_size = read(des->fd_i, &buf, (sizeof(uint64_t)))) > 0)
	{
		padding = (read_size < (int)(sizeof(uint64_t))) ?
			add_padding(read_size, &buf) : 100;
		process_des_chunk(buf, k, &final_buf[i]);
		i++;
		des_print(des, final_buf, &i, opts);
		buf = 0;
	}
	if (padding == 100)
		des_last_chunk(buf, final_buf, k, &i);
	if (i)
		(opts & OPT_A) ?
		b64_encode_buffer((t_base64 *)des, (char *)final_buf, i * 8) :
		write(des->fd_o, final_buf, i * 8);
}

void		des_ecb_algo(const uint32_t *ptr, t_chksum *sum, uint32_t opts)
{
	uint64_t	k[16];
	t_des		*des;
	uint64_t	final_buf[6];
	uint64_t	test;

	(void)sum;
	ft_bzero(final_buf, sizeof(uint64_t) * 6);
	des = (t_des *)ptr;
	if (des->pass)
	{
		ft_memcpy((uint8_t *)&final_buf[0], "Salted__", 8);
		test = endian_swap64((uint64_t)des->salt_val);
		ft_memcpy((uint8_t *)&final_buf[1], &test, 8);
	}
	des_gen_keytab(des->key_val, k);
	if (opts & OPT_PP)
		ft_fdprintf(2, "Key : %016.16llX\nVect: %016.16llX\nSalt:"
	"%016.16llX\nPass: %s\n", (des->key_val), (des->vec_val),
	(des->salt_val), des->pass);
	read_loop(des, k, final_buf, opts);
}
