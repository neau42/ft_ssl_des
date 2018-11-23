/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/24 00:13:10 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		ft_null(const uint32_t *buf, t_chksum *sum)
{
	(void)buf;
	(void)sum;
	ft_printf("___________________ft_null______________\n");
}

// void		sha256(const uint32_t *buf, t_chksum *sum)
// {
// 	(void)buf;
// 	(void)sum;
// }

void		algo(void *buf, t_chksum *sum, uint32_t opts)
{
	static void (*fcts[16])(const uint32_t *, t_chksum *) =
	{ft_null, md5, sha256, ft_null, ft_null, ft_null, ft_null, ft_null,
	ft_null, ft_null, ft_null, ft_null, ft_null, ft_null, ft_null, ft_null};

	fcts[opts & GET_HASH](buf, sum);
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
	if (opts & OPT_MD5)
	{
		if (file_name && (!(opts & (OPT_Q | OPT_R))))
			ft_printf("%s(%s)= ", "MD5", file_name);
			print_md5sum(sum->md5);
		if (opts & (OPT_R) && !(opts & OPT_Q) && file_name)
			ft_printf(" %s", file_name);
		ft_printf("\n");
	}
	else if (opts & OPT_SHA256)
	{
		if (file_name && (!(opts & (OPT_Q | OPT_R))))
			ft_printf("%s(%s)= ", "SHA256", file_name);
		print_sha256sum(sum->sha256);
		if (opts & (OPT_R) && !(opts & OPT_Q) && file_name)
			ft_printf(" %s", file_name);
		ft_printf("\n");
	}
}
