/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_chksum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 20:28:14 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	init_chksum(t_chksum *sum, uint32_t opts)
{
	if (opts & OPT_MD5)
	{
		sum->md5[0] = 0x67452301;
		sum->md5[1] = 0xEFCDAB89;
		sum->md5[2] = 0x98BADCFE;
		sum->md5[3] = 0x10325476;
	}
	else if (opts & OPT_SHA256)
	{
		sum->sha256[0] = 0x67452301;
		sum->sha256[1] = 0xEFCDAB89;
		sum->sha256[2] = 0x98BADCFE;
		sum->sha256[3] = 0x10325476;
		sum->sha256[4] = 0x42424242;
	}
}

void	init_chksum_n_read(t_chksum *sum, uint32_t opts, t_read *r)
{
	init_chksum(sum, opts);
	if (opts & OPT_MD5)
		r->bsz = 64;
	else
		r->bsz = 64;
	r->len = 0;
	r->size = 0;
	r->file_name = NULL;
}
