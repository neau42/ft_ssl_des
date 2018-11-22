/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 18:08:58 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void ft_null(const uint32_t *buf, t_chksum *sum)
{
	(void)buf;
	(void)sum;
}
void sha256(const uint32_t *buf, t_chksum *sum)
{
	(void)buf;
	(void)sum;
	ft_printf("___________________sha256______________\n");
}



void 		algo(void *buf, t_chksum *sum, uint32_t opts)
{
	static void (*fcts[4])(const uint32_t *, t_chksum *) =
		{ft_null, md5, sha256, ft_null};

		return (fcts[(opts & GET_HASH)](buf, sum));
}

void print_chksum(t_chksum *sum, char *file_name, uint32_t opts)
{
	if (file_name)
		ft_printf("%s(%s)= %08x%08x%08x%08x\n",
		((opts & GET_HASH) == OPT_MD5)? "MD5" : "SHA256",
		file_name, endian_swap32(sum->md5[0]), endian_swap32(sum->md5[1]), endian_swap32(sum->md5[2]), endian_swap32(sum->md5[3]));
	else
		ft_printf("%08x%08x%08x%08x\n", endian_swap32(sum->md5[0]), endian_swap32(sum->md5[1]), endian_swap32(sum->md5[2]), endian_swap32(sum->md5[3]));
}
