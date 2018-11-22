/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 02:23:00 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void 		read_stdin(uint32_t opts);
int			process_null(char *str, uint32_t opts)
{
	(void)str;
		ft_printf("process_null\n");
	if (!(opts & OPT_FILE) || opts & OPT_P)
	{
		ft_printf("\tread stdin\n");
		read_stdin(opts);
	}
	return (0);
}


void		format_last_string(t_read *r, uint32_t opts, t_result *res)
{
	if (r->len < 64)
		r->buf[r->len] = (1 << 7);
	if (r->len > (int)(SIZE_BUF - sizeof(uint64_t) - 1))
	{
		algo((uint32_t *)r->buf, opts, res);
		ft_bzero(r->buf, SIZE_BUF);
		if (r->len == SIZE_BUF - sizeof(uint64_t))
			r->buf[0] = (1 << 7);
	}
	else
	{
		if (r->len == 0 || r->len >= 64)
		{
			ft_bzero(r->buf, SIZE_BUF);
			r->len = 0;
			r->buf[0] = (1 << 7);
		}
	}
	// *(uint64_t *)((r->buf) + SIZE_BUF - sizeof(uint64_t)) = (r->size); //endian_swap64(size) ??
	
	
	int i = 0;
	while (i < 64)
	{
		*(uint64_t *)&r->buf[SIZE_BUF - sizeof(uint64_t)] = 0x1ULL << i;
		uint64_t test;
		test = ((*(uint64_t *)((r->buf) + SIZE_BUF - sizeof(uint64_t))));
		// ft_printf("\033[94m\nsize:\t\t{%064b} = %d\033[0m\n", r->size, r->size);
		ft_printf("\033[94mtest:\t\t{%064llb} = %lld\033[0m\n",test, test);
		algo((uint32_t *)r->buf, opts, res);
		i++;
	}
}

void init_result(t_result *r, uint32_t opts)
{
	if (opts & MD5_HASH)
	{
		r->md5[0] = 0x67452301;
		r->md5[1] = 0xEFCDAB89;
		r->md5[2] = 0x98BADCFE;
		r->md5[3] = 0x10325476;
	}
	else if (opts & SHA256_HASH)
	{
		r->sha256[0] = 0x67452301;
		r->sha256[1] = 0xEFCDAB89;
		r->sha256[2] = 0x98BADCFE;
		r->sha256[3] = 0x10325476;
		r->sha256[4] = 0x42424242;
	}
}

void read_stdin(uint32_t opts)
{
	t_read		r;
	uint8_t		result[16];
	t_result res;

	init_result(&res, opts);
	(void)opts;
	ft_printf("------------------------------- EXEC ON STDIN --------------------------------------\n");
	r.size = 0;
	while ((r.len = read(0, r.buf, SIZE_BUF)) > 0)
	{
		ft_printf(">>>> r.buf[%d] >>>>>>>>", r.len);
		if (r.len == 64)
		{
			// algo();
			print_memory_hex(r.buf, r.len);
		}
	}
	format_last_string(&r, opts, &res);
	result[0] = r.buf[0];
	return ;
}

int process_file(char *file_name, uint32_t opts)
{
	t_read		r;
	int			fd;
	t_result	res;

	init_result(&res, opts);
	r.size = 0;
	ft_printf("------------------------------- EXEC ON FILE --------------------------------------\n");
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_printf("%s: No such file or directory\n", file_name);
		return (-1);
	}
	ft_bzero(r.buf, SIZE_BUF);
	while ((r.len = read(fd, r.buf, SIZE_BUF)) == (int)(SIZE_BUF))
	{
		algo((uint32_t *)r.buf, opts, &res);
		ft_bzero(r.buf, SIZE_BUF);
		r.size += SIZE_BUF;
	}
	r.size += r.len;
	format_last_string(&r, opts, &res);
	close(fd);
	return (0);
}
