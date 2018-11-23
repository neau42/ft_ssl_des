/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:03:17 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/24 00:02:24 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t	r_rot(uint32_t n, unsigned int c)
{
	unsigned int mask;

	mask = (CHAR_BIT*sizeof(n) - 1);
	c &= mask;
	return (n >> c) | (n<<( (-c)&mask ));
}

void			init_schedule_array(uint32_t *w, const uint32_t *msg)
{
	const uint8_t	*p;
	int				i;

	i = -1;
	p = (const uint8_t *)msg - 4;
	while (++i < 16 && (p += 4))
		w[i] = (uint32_t) p[0] << 24 | (uint32_t) p[1] << 16 |
			(uint32_t) p[2] << 8 | (uint32_t) p[3];
	i = 15;
	while (++i < 64)
		w[i] = w[i - 16] + (r_rot(w[i - 15], 7)	^ r_rot(w[i - 15], 18)
			^ (w[i - 15] >> 3)) + w[i - 7] + 
			(r_rot(w[i - 2], 17) ^ r_rot(w[i - 2], 19) ^ (w[i - 2] >> 10));
}

void			sha_loop(uint32_t *abcdefgh, const uint32_t ki, uint32_t wi)
{
	uint32_t	temp1;
	uint32_t	temp2;

	temp1 = abcdefgh[7]
	+ (r_rot(abcdefgh[4], 6) ^ r_rot(abcdefgh[4], 11) ^ r_rot(abcdefgh[4], 25))
	+ ((abcdefgh[4] & abcdefgh[5]) ^ ((~abcdefgh[4]) & abcdefgh[6])) + ki + wi;
	temp2 =
	(r_rot(abcdefgh[0], 2) ^ r_rot(abcdefgh[0], 13) ^ r_rot(abcdefgh[0], 22))
	+ ((abcdefgh[0] & abcdefgh[1])
		^ (abcdefgh[0] & abcdefgh[2]) ^ (abcdefgh[1] & abcdefgh[2]));
	abcdefgh[7] = abcdefgh[6];
	abcdefgh[6] = abcdefgh[5];
	abcdefgh[5] = abcdefgh[4];
	abcdefgh[4] = abcdefgh[3] + temp1;
	abcdefgh[3] = abcdefgh[2];
	abcdefgh[2] = abcdefgh[1];
	abcdefgh[1] = abcdefgh[0];
	abcdefgh[0] = temp1 + temp2;
}

void			sha256(const uint32_t *msg, t_chksum *sum)
{
	static const uint32_t	k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5,	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3,	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
	uint32_t				abcdefgh[8];
	uint32_t				w[64];
	int						i;

	ft_memcpy(abcdefgh, sum->sha256, sizeof(uint32_t) * 8);
	init_schedule_array((uint32_t *)w, msg);
	i =	-1;
	while (++i < 64)
		sha_loop(abcdefgh, k[i], w[i]);
	i = -1;
	while (++i < 8)
		sum->sha256[i] += abcdefgh[i];
}
