/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/20 06:18:57 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		process_string(char *str, uint32_t opts)
{
	uint8_t		buf[SIZE_BUF];
	t_chksum	sum;
	uint32_t	len;
	uint64_t	size;

	ft_printf("process_string\n");
	ft_printf("\tEXEC md5 on '%s'\n", str);
	init_chksum(&sum, opts);
	size = 0;
	len = 0;
	ft_bzero(buf, 64);
	while ((len = ft_strlen(&str[len])) > SIZE_BUF)
	{
		ft_memcpy(buf, &str[len], SIZE_BUF);
		algo(buf, &sum, opts);
		ft_bzero(buf, 64);
		size += (SIZE_BUF * 8);
	}
	ft_memcpy(buf, &str[size / 8], len);
	ft_printf("len:%d\n", len);
	buf[len] = (1 << 7);
	size += (len*8);
	*(uint64_t *)&buf[SIZE_BUF - sizeof(uint64_t)] = (size);
	// print_memory_hex(buf, 64);
	algo(buf, &sum, opts);
	print_chksum(&sum, str, opts);
	return (0);
}
