/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_on_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/20 15:29:31 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void algo(void);


void read_stdin(uint32_t opts);
int		    ft_exec_on_null(char *str, uint32_t opts)
{
	(void)str;
		ft_printf("ft_exec_on_null\n");
	if (!(opts & OPT_FILE) || opts & OPT_P)
	{
		ft_printf("\tread stdin\n");
		read_stdin(opts);
	}
	return (0);
}


void format_last_string(t_read		*r, uint32_t opts)
{
    (void)opts;
	// size = nb_loop * SIZE_BUF + r->len;
	if (r->len < 64)
		r->buf[r->len] = 1;
	if (r->len > (int)(SIZE_BUF - sizeof(uint64_t) - 1))
	{
		algo();
		print_memory_hex(r->buf, SIZE_BUF);
		ft_bzero(r->buf, SIZE_BUF);
		if (r->len == SIZE_BUF - sizeof(uint64_t))
			r->buf[0] = 1;
	}
	else
	{
		if (r->len == 0 || r->len >= 64)
		{
			ft_bzero(r->buf, SIZE_BUF);
			r->len = 0;
			r->buf[0] = 1;
		}
	}
	*(uint64_t *)((uint8_t *)(r->buf) + SIZE_BUF - sizeof(uint64_t)) = r->size;//endian_swapp(size) ??
	algo();
	print_memory_hex(r->buf, SIZE_BUF);
}

void algo(void)
{
	int32_t r[64] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22, 5,  9, 14, 20,  5,  9, 14, 20,  5,  9,
	14, 20, 5, 9, 14, 20, 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, 6, 10, 15, 21,  6, 10, 15, 21,
	6, 10, 15, 21,  6, 10, 15, 21};
	int32_t k[64];
	int32_t h[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
	int i = -1;

	while (++i < 64)
	    k[i] = floor(fabs(sin(i + 1)) * 0x100000000);

	i = 0;
	ft_printf("tab K:\n");
	while (i< 64)
	{
		ft_printf("% 12d .", k[i++]);
		if (i%8 == 0)
			ft_printf("\n");
	}
	i = 0;
	ft_printf("tab R:\n");
	while (i< 64)
	{
		ft_printf("% 3d . ", r[i++]);
		if (i%8 == 0)
			ft_printf("\n");
	}
	i = 0;
	ft_printf("tab H:\n");
	while (i< 4)
	{
		ft_printf("% 8d . ", h[i++]);
		if (i%8 == 0)
			ft_printf("\n");
	}


}

int		    ft_exec_on_file(char *file_name, uint32_t opts)
{
	t_read		r;
	int			fd;
	uint8_t		result[CHKSUM_SIZE];

    (void)opts;
	fd = open(file_name, O_RDONLY);
	r.size = 0;
	ft_printf("------------------------------- EXEC ON FILE --------------------------------------\n");
	if (fd < 0)
	{
		ft_printf("%s: No such file or directory\n",file_name);
		return (-1);
	}
	ft_bzero(r.buf, SIZE_BUF);
	while ((r.len = read(fd, r.buf, SIZE_BUF)) == (int)(SIZE_BUF))
	{
		algo();
		print_memory_hex(r.buf, SIZE_BUF);
		ft_bzero(r.buf, SIZE_BUF);
		r.size += SIZE_BUF;
	}
	r.size += r.len;
	format_last_string(&r, opts);
	ft_printf("\n\nfinal size: %d\n\n",r.size);
	result[0] = r.buf[0];
	if (fd > 0)
		close(fd);
	return (0);
}


void read_stdin(uint32_t opts)
{
	t_read		r;
	uint8_t		result[16];	// (128 / 8)

    (void)opts;
	ft_printf("read stdin\n");
	r.size = 0;
	while ((r.len = read(0, r.buf, SIZE_BUF)) > 0)
	{
		ft_printf(">>>> r.buf[%d] >>>>>>>>", r.len);
		
		if (r.len == 64)
		{
			algo();
			print_memory_hex(r.buf, r.len);
		}
			//pseudo strncat(r.buf, tmp_bul, 64)
		//if r.len == 64 exec_algo
		//else concate
	}
	ft_printf("\n\nfinal size: %d\n\n",r.size);
	format_last_string(&r, opts);
	result[0] = r.buf[0];
	return ;
}

