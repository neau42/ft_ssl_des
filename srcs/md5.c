/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:03:17 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 02:04:26 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// uint32_t k1[64];
// while (++i < 64)
//	k1[i] = floor(fabs(sin(i + 1)) * 0x100000000);

// int32_t ft_f(int32_t b, int32_t c, int32_t d)
// {
// 	return ((b & c) | (~b & d));
// }

// int32_t ft_g(int32_t b, int32_t c, int32_t d)
// {
// 	return ((b & d) | (c & ~d));
// }

// int32_t ft_h(int32_t b, int32_t c, int32_t d)
// {
// 	return (b ^ c ^ d);
// }

// int32_t ft_i(int32_t b, int32_t c, int32_t d)
// {
// 	return (c ^ (b | ~d));
// }

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

static uint32_t		*get_constant_s(void)
{
	static uint32_t s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9,
		14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11,
		16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

	return (s);
}

void init_vars(uint32_t **k, uint32_t **s, uint32_t *abcdfgi, t_result *r)
{
	*k = get_constant_k();
	*s = get_constant_s();
	abcdfgi[0] = r->md5[0];
	abcdfgi[1] = r->md5[1];
	abcdfgi[2] = r->md5[2];
	abcdfgi[3] = r->md5[3];
	abcdfgi[6] = 0;
}

void	algo(uint32_t *msg, uint32_t opts, t_result *r)
{
	uint32_t	*s;
	uint32_t	*k;
	uint32_t	vars[7];

	init_vars(&k, &s, vars, r);
	(void)opts;
	print_memory_hex(msg, SIZE_BUF);
	while (vars[6] < 64)
	{
		if (vars[6] <= 15 && ((vars[5] = vars[6]) || 1))
			vars[4] = (vars[1] & vars[2]) | (~vars[1] & vars[3]);
		else if (vars[6] <= 31 && ((vars[5] = (5 * vars[6] + 1) % 16) || 1))
			vars[4] = (vars[1] & vars[3]) | (vars[2] & ~vars[3]) ;
		else if (vars[6] <= 47 && ((vars[5] = (3 * vars[6] + 5) % 16) || 1))
			vars[4] = vars[1] ^ vars[2] ^ vars[3];
		else if ((vars[5] = (7 * vars[6]) % 16) || 1)
			vars[4] = (vars[2] ^ (vars[1] | ~vars[3])) ;
		vars[4] = vars[4] + vars[0] + k[vars[6]] + msg[vars[5]];
		vars[0] = vars[3];
		vars[3] = vars[2];
		vars[2] = vars[1];
		vars[1] += (vars[4] << s[vars[6]]) | (vars[4] >> (32 - s[vars[6]]));
		vars[6]++;
	}
	r->md5[0] += vars[0];
	r->md5[1] += vars[1];
	r->md5[2] += vars[2];
	r->md5[3] += vars[3];
	r->md5[0] = endian_swap32(r->md5[0]);
	r->md5[1] = endian_swap32(r->md5[1]);
	r->md5[2] = endian_swap32(r->md5[2]);
	r->md5[3] = endian_swap32(r->md5[3]);
	ft_printf("MD5(vide)= %x%x%x%x\n", r->md5[0], r->md5[1], r->md5[2], r->md5[3]);
	ft_printf("~~~~~~~~~~~~~~~~~\n");
}
 