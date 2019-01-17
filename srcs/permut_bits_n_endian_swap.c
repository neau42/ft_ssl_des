/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permut_bits_n_endian_swap.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/17 18:46:36 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	endian_swap32(uint32_t x)
{
	return (((x & 0x000000FF) << 24) | ((x & 0x0000FF00) << 8)
	| (((x & 0x00FF0000) >> 8) | ((x & 0xFF000000) >> 24)));
}

uint64_t	endian_swap64(uint64_t x)
{
	return (((x & 0x00000000000000FF) << 56)
		| ((x & 0x000000000000FF00) << 40)
		| ((x & 0x0000000000FF0000) << 24)
		| ((x & 0x00000000FF000000) << 8)
		| ((x & 0x000000FF00000000) >> 8)
		| ((x & 0x0000FF0000000000) >> 24)
		| ((x & 0x00FF000000000000) >> 40)
		| ((x & 0xFF00000000000000) >> 56));
}

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

uint64_t	unpermut_bits(uint64_t len, uint64_t value, uint8_t *permut_tab)
{
	int			i;
	uint64_t	ret;

	i = -1;
	ret = 0;
	while (++i < (int)len)
		ret |= (((value >> (len - i - 1)) & 1) << (len - permut_tab[i]));
	return (ret);
}

uint64_t	str_to_uint64(unsigned char *str)
{
	return ((uint64_t)str[7] | (uint64_t)str[6] << 8
	| (uint64_t)str[5] << 16 | (uint64_t)str[4] << 24
	| (uint64_t)str[3] << 32 | (uint64_t)str[2] << 40
	| (uint64_t)str[1] << 48 | (uint64_t)str[0] << 56);
}
