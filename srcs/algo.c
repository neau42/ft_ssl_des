/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/18 23:40:28 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		ft_null(const uint32_t *buf, t_chksum *sum, uint32_t opts)
{
	(void)buf;
	(void)sum;
	(void)opts;
}

void		algo(void *buf, t_chksum *sum, uint32_t opts)
{
	static void (*fcts[11])(const uint32_t *, t_chksum *, uint32_t) = {
		ft_null, md5, sha256, ft_null, des_algo, des_algo, des_algo,
		des_algo, des_algo, des_algo, des_algo};

	if (opts & OPT_DD)
		print_memory_hex(buf, 64);
	fcts[opts & GET_HASH](buf, sum, opts);
}

void		print_sha256sum(uint32_t *sum)
{
	ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x", sum[0], sum[1],
	sum[2], sum[3], sum[4], sum[5], sum[6], sum[7]);
}

void		print_md5sum(uint32_t *sum)
{
	ft_printf("%08x%08x%08x%08x", endian_swap32(sum[0]),
	endian_swap32(sum[1]), endian_swap32(sum[2]),
	endian_swap32(sum[3]));
}

void		print_chksum(t_chksum *sum, char *file_name, uint32_t opts)
{
	if ((opts & GET_HASH) == OPT_MD5)
	{
		if (file_name && (!(opts & (OPT_Q | OPT_R))))
			ft_printf("%s(%s)= ", "MD5", file_name);
		print_md5sum(sum->md5);
		if (file_name && (opts & (OPT_R | OPT_Q)) == OPT_R)
			ft_printf(" %s", file_name);
		ft_printf("\n");
	}
	else if ((opts & GET_HASH) == OPT_SHA256)
	{
		if (file_name && (!(opts & (OPT_Q | OPT_R))))
			ft_printf("%s(%s)= ", "SHA256", file_name);
		print_sha256sum(sum->sha256);
		if (file_name && (opts & (OPT_R | OPT_Q)) == OPT_R)
			ft_printf(" %s", file_name);
		ft_printf("\n");
	}
}
