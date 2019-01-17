/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_des_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 04:00:08 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/17 18:31:20 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t		ft_f(uint32_t right, uint64_t key)
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
		result |= ((g_s[i][((b[i] & 0x1E) >> 1) + 16 * (((b[i] & 0x20) >> 4)
					+ (b[i] & 0x1))]) << (28 - (i * 4)));
	return (permut_bits(32, 32, result, g_p));
}

static uint64_t	ft_des_rounds(uint64_t msg, uint64_t *k)
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

void			process_des_chunk(t_des *des, uint64_t *k, uint64_t *final_buf,
																uint32_t opts)
{
	uint64_t	result;

	(void)opts;
	if ((opts & GET_HASH) == OPT_CBC)
		des->buf ^= endian_swap64(des->vec_val);
	des->buf = endian_swap64(des->buf);
	result = endian_swap64(permut_bits(64, 64, ft_des_rounds(permut_bits(
	64, 64, des->buf, g_ip), k), g_ip_rev));
	ft_memcpy((uint8_t *)final_buf, (void *)&result, 8);
	if ((opts & GET_HASH) == OPT_CBC)
		des->vec_val = endian_swap64(result);
}
