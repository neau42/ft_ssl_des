/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:03:17 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/16 16:13:02 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const uint32_t	g_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void			sha_loop(uint32_t *abcd, uint32_t *w)
{
	uint32_t	tmp1;
	uint32_t	tmp2;
	int			i;

	i = -1;
	while (++i < 64)
	{
		tmp1 = abcd[7]
		+ (r_rot(abcd[4], 6) ^ r_rot(abcd[4], 11) ^ r_rot(abcd[4], 25))
		+ ((abcd[4] & abcd[5]) ^ ((~abcd[4]) & abcd[6])) + g_k[i] + w[i];
		tmp2 = (r_rot(abcd[0], 2) ^ r_rot(abcd[0], 13) ^ r_rot(abcd[0], 22))
		+ ((abcd[0] & abcd[1]) ^ (abcd[0] & abcd[2]) ^ (abcd[1] & abcd[2]));
		abcd[7] = abcd[6];
		abcd[6] = abcd[5];
		abcd[5] = abcd[4];
		abcd[4] = abcd[3] + tmp1;
		abcd[3] = abcd[2];
		abcd[2] = abcd[1];
		abcd[1] = abcd[0];
		abcd[0] = tmp1 + tmp2;
	}
}

void			sha256(const uint32_t *msg, t_chksum *sum, uint32_t opts)
{
	uint32_t				abcdefgh[8];
	uint32_t				w[64];
	int						i;

	(void)opts;
	ft_memcpy(abcdefgh, sum->sha256, sizeof(uint32_t) * 8);
	i = -1;
	while (++i < 16)
		w[i] = endian_swap32(msg[i]);
	i = 15;
	while (++i < 64)
		w[i] = w[i - 16] + (r_rot(w[i - 15], 7) ^ r_rot(w[i - 15], 18)
		^ (w[i - 15] >> 3)) + w[i - 7]
		+ (r_rot(w[i - 2], 17) ^ r_rot(w[i - 2], 19) ^ (w[i - 2] >> 10));
	sha_loop(abcdefgh, w);
	i = -1;
	while (++i < 8)
		sum->sha256[i] += abcdefgh[i];
}
