/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:03:17 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 06:49:37 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t		*get_constant_k(void)
{
	static uint32_t k[64] = {
			0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
			0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
			0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
			0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
			0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
			0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
			0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
			0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
			0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
			0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
			0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	return (k);
}

static void		    init_vars(uint32_t **k, uint32_t **s, uint32_t *abcdfgi,
					t_chksum *r)
{
	static uint32_t t[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9,
		14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11,
		16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

	if (!*s)
	{
		*k = get_constant_k();
		*s = t;
	}
	abcdfgi[0] = r->md5[0];
	abcdfgi[1] = r->md5[1];
	abcdfgi[2] = r->md5[2];
	abcdfgi[3] = r->md5[3];
	abcdfgi[6] = -1;
}

void				md5(uint32_t *msg, t_chksum *sum)
{
	static uint32_t	*s = NULL;
	static uint32_t	*k = NULL;
	uint32_t		abcdf[7];

	init_vars(&k, &s, abcdf, sum);
	print_memory_hex(msg, SIZE_BUF);
	while (++abcdf[6] < 64)
	{
		if (abcdf[6] <= 15 && ((abcdf[5] = abcdf[6]) || 1))
			abcdf[4] = (abcdf[1] & abcdf[2]) | (~abcdf[1] & abcdf[3]);
		else if (abcdf[6] <= 31 && ((abcdf[5] = (5 * abcdf[6] + 1) % 16) || 1))
			abcdf[4] = (abcdf[1] & abcdf[3]) | (abcdf[2] & ~abcdf[3]) ;
		else if (abcdf[6] <= 47 && ((abcdf[5] = (3 * abcdf[6] + 5) % 16) || 1))
			abcdf[4] = abcdf[1] ^ abcdf[2] ^ abcdf[3];
		else if ((abcdf[5] = (7 * abcdf[6]) % 16) || 1)
			abcdf[4] = (abcdf[2] ^ (abcdf[1] | ~abcdf[3]));
		abcdf[4] = abcdf[4] + abcdf[0] + k[abcdf[6]] + msg[abcdf[5]];
		abcdf[0] = abcdf[3];
		abcdf[3] = abcdf[2];
		abcdf[2] = abcdf[1];
		abcdf[1] += (abcdf[4] << s[abcdf[6]]) | (abcdf[4] >> (32 - s[abcdf[6]]));
	}
	sum->md5[0] = endian_swap32(sum->md5[0] + abcdf[0]);
	sum->md5[1] = endian_swap32(sum->md5[1] + abcdf[1]);
	sum->md5[2] = endian_swap32(sum->md5[2] + abcdf[2]);
	sum->md5[3] = endian_swap32(sum->md5[3] + abcdf[3]);
}
 