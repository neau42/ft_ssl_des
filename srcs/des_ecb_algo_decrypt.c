/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_algo_decrypt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:35:57 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/12 17:29:39 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	ft_des_rounds_rev(uint64_t msg, uint64_t *k)
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

	result = endian_swap64(unpermut_bits(64, ft_des_rounds_rev(unpermut_bits(64, endian_swap64(msg), g_ip_rev), k), g_ip));
	pad = result >> 56;
	write(des->fd_o, &result, 8 - pad);
}

void	des_ecb_algo_decrypt(t_des *des, uint32_t opts)
{
	uint64_t	k[16];
	uint64_t	result;
	int			read_size;
	uint64_t	buf;
	uint64_t	msg;

	msg = 0;
	des_gen_keytab(des->key_val, k);
	while ((read_size = read(des->fd_i, &buf, (sizeof(uint64_t)))) > 0)
	{
		if (msg)
		{
			result = endian_swap64(unpermut_bits(64, ft_des_rounds_rev(unpermut_bits(64, endian_swap64(msg), g_ip_rev), k), g_ip));
			write(des->fd_o, &result, 8);
		}
		msg = buf;
	}
	last_chunk_rm_padd(msg, k, des);
	if (opts & OPT_PP)
		ft_fdprintf(2, "Key : %016.16llX\nVect: %016.16llX\nSalt: %016.16llX\nPass: %s\n",
					(des->key_val), (des->vec_val), (des->salt_val), des->pass);
}
