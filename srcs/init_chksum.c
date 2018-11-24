/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_chksum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/24 05:31:25 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	init_chksum(t_chksum *sum, uint32_t opts)
{
	
	if ((opts & GET_HASH) == OPT_MD5)
	{
		sum->md5[0] = 0x67452301;
		sum->md5[1] = 0xEFCDAB89;
		sum->md5[2] = 0x98BADCFE;
		sum->md5[3] = 0x10325476;
	}
	else if ((opts & GET_HASH) == OPT_SHA256)
	{
		// sum->sha256[0] = endian_swap32(0x6a09e667);
		// sum->sha256[1] = endian_swap32(0xbb67ae85);
		// sum->sha256[2] = endian_swap32(0x3c6ef372);
		// sum->sha256[3] = endian_swap32(0xa54ff53a);
		// sum->sha256[4] = endian_swap32(0x510e527f);
		// sum->sha256[5] = endian_swap32(0x9b05688c);
		// sum->sha256[6] = endian_swap32(0x1f83d9ab);
		// sum->sha256[7] = endian_swap32(0x5be0cd19);
		sum->sha256[0] = 0x6a09e667;
		sum->sha256[1] = 0xbb67ae85;
		sum->sha256[2] = 0x3c6ef372;
		sum->sha256[3] = 0xa54ff53a;
		sum->sha256[4] = 0x510e527f;
		sum->sha256[5] = 0x9b05688c;
		sum->sha256[6] = 0x1f83d9ab;
		sum->sha256[7] = 0x5be0cd19;
	}
}

void	init_chksum_n_read(t_chksum *sum, uint32_t opts, t_read *r,
														uint8_t *buf)
{
	init_chksum(sum, opts);
	// if ((opts & GET_HASH) == OPT_MD5)
	// 	r->bsz = 64;
	// else if ((opts & GET_HASH) == OPT_SHA256)
		r->bsz = 64;
	r->len = 0;
	r->size = 0;
	r->file_name = NULL;
	r->buf = buf;
	ft_bzero(r->buf, r->bsz);
}
