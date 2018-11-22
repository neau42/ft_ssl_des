/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_chksum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 18:12:38 by no               ###   ########.fr       */
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