/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_algo_decrypt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:35:57 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/16 16:21:04 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint64_t	ft_des_rounds_rev(uint64_t msg, uint64_t *k)
{
	uint32_t	left;
	uint32_t	right;
	uint32_t	tmp_right;
	int			i;

	left = msg;
	right = (msg >> 32);
	i = 16;
	while (--i >= 0)
	{
		tmp_right = right;
		right = left;
		left = tmp_right ^ ft_f(left, k[i]);
	}
	return (right + ((uint64_t)left << 32));
}

static void	last_chunk_rm_padd(uint64_t msg, uint64_t *k, t_des *des)
{
	uint64_t	result;
	uint8_t		pad;
	int			pad_save;

	result = endian_swap64(unpermut_bits(64, ft_des_rounds_rev(
	unpermut_bits(64, endian_swap64(msg), g_ip_rev), k), g_ip));
	pad = result >> 56;
	pad_save = pad;
	while (pad_save > 0)
	{
		if ((result >> (64 - (pad_save * 8)) & 0xff) != pad)
		{
			write(des->fd_o, &result, 8 - pad);
			ft_printf("bad decrypt\n");
			return ;
		}
		pad_save--;
	}
	write(des->fd_o, &result, 8 - pad);
}

static void		decode_msg(t_des *des, uint64_t *msg, uint64_t *k, int size)
{
	uint64_t	result;

	while (size-- > 0)
	{
		result = endian_swap64(unpermut_bits(64, ft_des_rounds_rev(
		unpermut_bits(64, endian_swap64(*msg), g_ip_rev), k), g_ip));
		write(des->fd_o, &result, 8);
		msg++;
	}
}

static int	format_buf(char *b64_buf, char *final_buf, int size, uint64_t *msg)
{
	int final_size;

	b64_decode_str(b64_buf, final_buf, size);
	final_size = (size / 8 * 6 / 8) + ((size % 8) ? 1 : 0) - 1;
	ft_memcpy(msg, final_buf, (final_size + 1) * 8);
	return (final_size);
}

int			get_size(int size)
{
	return (((size / 8) + ((size % 8) ? 1 : 0) - 1));
}

void		des_ecb_algo_decrypt(t_des *des, uint32_t o, uint64_t *buf)
{
	uint64_t	k[16];
	uint64_t	msg[6];
	char		b64_buf[65];
	char		final_buf[49];
	int			sz;

	des_gen_keytab(des->key_val, k);
	ft_bzero(final_buf, 49);
	while (buf[1])
	{
		decode_msg(des, buf++, k, 1);
		buf[-1] = buf[0];
	}
	while ((!(o & OPT_A) && (sz = read(des->fd_i, &msg, 48)) > 0)
	|| ((o & OPT_A) && (sz = read_trim(des->fd_i, b64_buf, 64)) > 0))
	{
		if (buf[0])
			decode_msg(des, &buf[0], k, 1);
		sz = (o & OPT_A) ? format_buf(b64_buf, final_buf, sz, msg) :
			get_size(sz);
		buf[0] = msg[sz];
		decode_msg(des, msg, k, sz);
		ft_bzero(final_buf, 49);
	}
	last_chunk_rm_padd(buf[0], k, des);
}
