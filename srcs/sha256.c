/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:03:17 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/23 22:31:10 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// static uint32_t		*get_constant_k(void)
// {
// static uint32_t	k[64] = {
// 	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
// 	0x923f82a4, 0xab1c5ed5,	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
// 	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
// 	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
// 	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
// 	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
// 	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
// 	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
// 	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
// 	0x5b9cca4f, 0x682e6ff3,	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
// 	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

// 	return (k);
// }

static inline uint32_t rightrotate(uint32_t n, unsigned int c)
{
	// unsigned int mask;

	// mask = (CHAR_BIT*sizeof(n) - 1);
	// c &= mask;
	// return (n >> c) | (n<<( (-c)&mask ));

	return ((int)((unsigned)n >> c) | (n << (32 - c)));
}

void				sha256(const uint32_t *msg, t_chksum *sum)
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

	uint32_t		w[64] = {0};
	int				i = 0;
	uint32_t		s0;
	uint32_t		s1;
	uint32_t		a,b,c,d,e,f,g,h;
	uint32_t		ch, temp1, temp2, maj;

	// if (!k)
	// 	k = get_constant_k();
	// ft_memcpy(w, msg, 64);

	const uint8_t *p = (const uint8_t *)msg;

	i = -1;
	while (++i < 16)
	{
		w[i] = (uint32_t) p[0] << 24 | (uint32_t) p[1] << 16 |
			(uint32_t) p[2] << 8 | (uint32_t) p[3];
		p += 4;
	}

	// ft_printf("msg:\n");
	// print_memory_hex((void *)msg, 64);
	// ft_printf("before. w:\n");
	// print_memory_hex((void *)w, sizeof(w));
	i = 15;
	while (++i < 64)
	{
		s0 = rightrotate(w[i - 15], 7) ^ rightrotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s1 = rightrotate(w[i - 2], 17) ^ rightrotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;

	}
	// ft_printf("after. w = %%x: 0x%x:0x%x\n", w[0], endian_swap32(w[0]));
	// print_memory_hex((void *)w, sizeof(w));
	a = sum->sha256[0];
	b = sum->sha256[1];
	c = sum->sha256[2];
	d = sum->sha256[3];
	e = sum->sha256[4];
	f = sum->sha256[5];
	g = sum->sha256[6];
	h = sum->sha256[7];
	// ft_printf("\tbefore hash:\n");
	// ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x\n", endian_swap32(a), endian_swap32(b),
	// endian_swap32(c), endian_swap32(d),	endian_swap32(e), endian_swap32(f), endian_swap32(g), endian_swap32(h));
	i = -1;
	while (++i < 64)
	{
		s1 = rightrotate(e, 6) ^ rightrotate(e, 11) ^ rightrotate(e, 25);
		ch = (e & f) ^ ((~e) & g);
		temp1 = h + s1 + ch + k[i] + w[i];
		s0 = rightrotate(a, 2) ^ rightrotate(a, 13) ^ rightrotate(a, 22);
		maj = (a & b) ^ (a & c) ^ (b & c);
		temp2 = s0 + maj;
		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = c;
		c = b;
		b = a;
		a = temp1 + temp2;
	}
	sum->sha256[0] += a;
	sum->sha256[1] += b;
	sum->sha256[2] += c;
	sum->sha256[3] += d;
	sum->sha256[4] += e;
	sum->sha256[5] += f;
	sum->sha256[6] += g;
	sum->sha256[7] += h;
	return;
}
