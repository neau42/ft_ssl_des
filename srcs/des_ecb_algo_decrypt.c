/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_algo_decrypt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:35:57 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/11 23:37:52 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// extern uint8_t g_ip_rev[];

	// static uint8_t g_ip_rev[] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55,
	// 							 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	// 							 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10,
	// 							 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};

	// uint64_t	ft_des_rounds_rev(uint64_t msg, uint64_t *k)
	// {
	// 	uint32_t	left;
	// 	uint32_t	right;
	// 	uint32_t	tmp_left;
	// 	int			i;

	// 	right = msg;
	// 	left = (msg >> 32);
	// 	i = 0;
	// 	while (++i < 17)
	// 	{
	// 		tmp_left = left;
	// 		left = right;
	// 		right = tmp_left ^ ft_f(right, k[i - 1]);
	// 	}
	// 	return (left + ((uint64_t)right << 32));
	// }

// 	uint64_t
// 	rm_padding(int read_size, uint64_t *buf)
// {
// 	uint64_t padding;
// 	uint64_t padding_nb;

// 	padding = (int)(sizeof(uint64_t)) - read_size;
// 	padding_nb = (int)(sizeof(uint64_t)) - read_size;
// 	while (padding_nb-- > 0)
// 		*buf |= (padding << (uint64_t)(64 - (padding_nb + 1) * 8));
// 	return (padding);
// }


// gauche = droite - 1
// droite = gauche - 1 ^ f(droite - 1)

// droite = gauche + 1
// gauche = droite + 1 ^ f(gauche + 1)

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
	uint64_t	buf;

	// ft_printf("des_decode, des->key_val: %016llx\n", des->key_val);
	des_gen_keytab(des->key_val, k);
	while ((read_size = read(des->fd_i, &buf, (sizeof(uint64_t)))) > 0)
	{
		buf = endian_swap64(buf);
		result = unpermut_bits(64, ft_des_rounds_rev(unpermut_bits(64, buf, g_ip_rev), k), g_ip);
		ft_fdprintf(2, "result: %016llx\n", result, result);
		result = endian_swap64(result);
		ft_fdprintf(2, "last  : %016llx\n", result, result);
		write(des->fd_o, &result, 8);
	}
	if (opts & OPT_PP)
		ft_fdprintf(2, "Key : %016.16llX\nVect: %016.16llX\nSalt: %016.16llX\nPass: %s\n",
					(des->key_val), (des->vec_val), (des->salt_val), des->pass);
}
