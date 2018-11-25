/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_chksum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/25 09:42:15 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// void	init_chksum(t_chksum *sum, uint32_t opts)
// {
// 	if ((opts & GET_HASH) == OPT_MD5)
// 	{
// 		sum->md5[0] = 0x67452301;
// 		sum->md5[1] = 0xEFCDAB89;
// 		sum->md5[2] = 0x98BADCFE;
// 		sum->md5[3] = 0x10325476;
// 	}
// 	else if ((opts & GET_HASH) == OPT_SHA256)
// 	{
// 		sum->sha256[0] = 0x6a09e667;
// 		sum->sha256[1] = 0xbb67ae85;
// 		sum->sha256[2] = 0x3c6ef372;
// 		sum->sha256[3] = 0xa54ff53a;
// 		sum->sha256[4] = 0x510e527f;
// 		sum->sha256[5] = 0x9b05688c;
// 		sum->sha256[6] = 0x1f83d9ab;
// 		sum->sha256[7] = 0x5be0cd19;
// 		// 0x6a09e667;
// 		// 0xbb67ae85;
// 		// 0x3c6ef372;
// 		// 0xa54ff53a;
// 		// 0x510e527f;
// 		// 0x9b05688c;
// 		// 0x1f83d9ab;
// 		// 0x5be0cd19;
// 	}
// }
void	init_chksum(t_chksum *sum, uint32_t opts)
{
	static uint32_t chksum[GET_HASH][8] = { {0x00000000},
		{0x67452301, 0xEFCDAB89, 0x98BADCFE,0x10325476},
		{0x6a09e667, 0xbb67ae85, 0x3c6ef372,
			0xa54ff53a,	0x510e527f, 0x9b05688c, 0x1f83d9ab,0x5be0cd19}};

	if ((opts & GET_HASH) == OPT_MD5)
		ft_memcpy(sum->md5, chksum[OPT_MD5], CHKSUM_SIZE_MD5);
	else if ((opts & GET_HASH) == OPT_SHA256)
		ft_memcpy(sum->sha256, chksum[OPT_SHA256], CHKSUM_SIZE_SHA);
}

void	init_chksum_n_read(t_chksum *sum, uint32_t opts, t_read *r,
														uint8_t *buf)
{
	init_chksum(sum, opts);
	if ((opts & GET_HASH) == OPT_MD5)
		r->bsz = 64;
	else if ((opts & GET_HASH) == OPT_SHA256)
		r->bsz = 64;
	r->len = 0;
	r->size = 0;
	r->file_name = NULL;
	r->buf = buf;
	ft_bzero(r->buf, r->bsz);
}
