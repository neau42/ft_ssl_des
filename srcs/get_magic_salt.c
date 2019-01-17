/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_magic_salt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/17 18:45:33 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			get_magic_salt(int fd, uint64_t *salt_val, uint32_t opts,
											uint64_t *buf_save)
{
	char			buf[65];
	unsigned char	*ptr;

	ft_bzero(buf, 65);
	if ((opts & OPT_A
	&& (read_trim(fd, buf, 64) < 32))
	|| (!(opts & OPT_A) && (read(fd, buf, 16) < 16)
	&& ft_fdprintf(2, "error reading input file\n")))
		return (0);
	if (opts & OPT_A)
	{
		b64_decode_str((char *)buf, (char *)buf_save, 65);
		ptr = (unsigned char *)buf_save;
	}
	else
		ptr = (unsigned char *)buf;
	if (ft_strncmp("Salted__", (char *)ptr, 8))
	{
		ft_fdprintf(2, "bad magic number\n");
		return (0);
	}
	*salt_val = str_to_uint64(&ptr[8]);
	return (1);
}
