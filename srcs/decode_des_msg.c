/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_des_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:35:57 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/17 18:27:42 by nboulaye         ###   ########.fr       */
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

void		decode_des_msg(t_des *des, uint64_t *msg, int size, uint32_t opts)
{
	uint64_t		result;
	uint64_t		tmp_vector;
	static uint64_t	*k = NULL;

	if (k == NULL)
		k = des_gen_keytab(des->key_val);
	while (size-- > 0)
	{
		if ((opts & GET_HASH) == OPT_CBC)
			tmp_vector = endian_swap64(*msg);
		result = endian_swap64(unpermut_bits(64, ft_des_rounds_rev(
		unpermut_bits(64, endian_swap64(*msg), g_ip_rev), k), g_ip));
		if ((opts & GET_HASH) == OPT_CBC)
		{
			result ^= endian_swap64(des->vec_val);
			des->vec_val = tmp_vector;
		}
		write(des->fd_o, &result, 8);
		msg++;
	}
}
