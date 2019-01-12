/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_algo_decrypt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:35:57 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/12 17:05:24 by nboulaye         ###   ########.fr       */
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

void	des_ecb_algo_decrypt(t_des *des, uint32_t opts)
{
	uint64_t	k[16];
	uint64_t	result;
	int			read_size;
	uint64_t	buf[2];

	des_gen_keytab(des->key_val, k);
	while ((read_size = read(des->fd_i, &buf, (sizeof(uint64_t) * 2))) > 0)
	{
		ft_printf("read size: %d\n", read_size);
		buf[0] = endian_swap64(buf[0]);
		result = unpermut_bits(64, ft_des_rounds_rev(unpermut_bits(64, buf[0], g_ip_rev), k), g_ip);
		ft_fdprintf(2, "result: %016llx\n", result, result);
		result = endian_swap64(result);
		ft_fdprintf(2, "last  : %016llx\n", result, result);
		write(des->fd_o, &result, 8);
	}
	if (opts & OPT_PP)
		ft_fdprintf(2, "Key : %016.16llX\nVect: %016.16llX\nSalt: %016.16llX\nPass: %s\n",
					(des->key_val), (des->vec_val), (des->salt_val), des->pass);
}
