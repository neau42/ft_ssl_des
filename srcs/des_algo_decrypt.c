/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algo_decrypt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:35:57 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/17 18:15:12 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	last_chunk_rm_padd(uint64_t msg, t_des *des, uint32_t opts)
{
	uint64_t		result;
	uint8_t			pad;
	int				pad_save;
	static uint64_t *k = NULL;

	if (k == NULL)
		k = des_gen_keytab(des->key_val);
	result = endian_swap64(unpermut_bits(64, ft_des_rounds_rev(
	unpermut_bits(64, endian_swap64(msg), g_ip_rev), k), g_ip));
	if ((opts & GET_HASH) == OPT_CBC)
		result ^= endian_swap64(des->vec_val);
	pad = result >> 56;
	pad_save = pad;
	while (pad_save > 0)
	{
		if ((result >> (64 - (pad_save * 8)) & 0xff) != pad)
		{
			write(des->fd_o, &result, 8 - pad);
			ft_fdprintf(2, "bad decrypt\n");
			return ;
		}
		pad_save--;
	}
	write(des->fd_o, &result, 8 - pad);
}

static int	format_buf(char *b64_buf, char *final_buf, int size, uint64_t *msg)
{
	int final_size;

	b64_decode_str(b64_buf, final_buf, size);
	final_size = (size / 8 * 6 / 8) + ((size % 8) ? 1 : 0) - 1;
	ft_memcpy(msg, final_buf, (final_size + 1) * 8);
	return (final_size);
}

int			get_uint64_size(int size)
{
	return (((size / 8) + ((size % 8) ? 1 : 0) - 1));
}

void		des_algo_decrypt(t_des *des, uint32_t opts, uint64_t *buf)
{
	uint64_t	msg[6];
	char		b64_buf[65];
	char		final_buf[49];
	int			sz;

	ft_bzero(final_buf, 49);
	while (buf[1])
	{
		decode_des_msg(des, buf++, 1, opts);
		buf[-1] = buf[0];
	}
	while ((!(opts & OPT_A) && (sz = read(des->fd_i, &msg, 48)) > 0)
	|| ((opts & OPT_A) && (sz = read_trim(des->fd_i, b64_buf, 64)) > 0))
	{
		if (buf[0])
			decode_des_msg(des, &buf[0], 1, opts);
		sz = (opts & OPT_A) ? format_buf(b64_buf, final_buf, sz, msg) :
			get_uint64_size(sz);
		buf[0] = msg[sz];
		decode_des_msg(des, msg, sz, opts);
		ft_bzero(final_buf, 49);
	}
	last_chunk_rm_padd(buf[0], des, opts);
}
