/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 06:31:36 by no               ###   ########.fr       */
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


void		format_last_string(t_read *r, uint32_t opts, t_chksum *sum)
{
	(void)opts;
	if (r->len < r->bsz)
		r->buf[r->len] = (1 << 7);
	if (r->len > (int)(r->bsz - sizeof(uint64_t) - 1))
	{
		md5((uint32_t *)r->buf, sum);
		ft_bzero(r->buf, r->bsz);
		if (r->len == r->bsz - sizeof(uint64_t))
			r->buf[0] = (1 << 7);
	}
	else if (r->len == 0 || r->len >= r->bsz)
	{
		ft_bzero(r->buf, r->bsz);
		r->len = 0;
		r->buf[0] = (1 << 7);
	}
	// while (i < r->bsz)
	// {
		// *(uint64_t *)&r->buf[r->bsz - sizeof(uint64_t)] = 0x1ULL << i;
		*(uint64_t *)&r->buf[r->bsz - sizeof(uint64_t)] = r->size;
		// uint64_t test;
		// test = ((*(uint64_t *)((r->buf) + r->bsz - sizeof(uint64_t))));
		// ft_printf("\033[94m\nsize:\t\t{%064b} = %d\033[0m\n", r->size, r->size);
	ft_printf("\033[94mtest:\t\t{%064llb} = %lld\033[0m\n",((*(uint64_t *)((r->buf) + r->bsz - sizeof(uint64_t)))), ((*(uint64_t *)((r->buf) + r->bsz - sizeof(uint64_t)))));
	md5((uint32_t *)r->buf, sum);
		// i++;
	ft_printf("MD5(vide)= %x%x%x%x\n", sum->md5[0], sum->md5[1], sum->md5[2], sum->md5[3]);

	// }
}

void init_chksum(t_chksum *sum, uint32_t opts, t_read *r)
{
	if (opts & MD5_HASH)
	{
		sum->md5[0] = 0x67452301;
		sum->md5[1] = 0xEFCDAB89;
		sum->md5[2] = 0x98BADCFE;
		sum->md5[3] = 0x10325476;
		r->bsz = 64;
	}
	else if (opts & SHA256_HASH)
	{
		sum->sha256[0] = 0x67452301;
		sum->sha256[1] = 0xEFCDAB89;
		sum->sha256[2] = 0x98BADCFE;
		sum->sha256[3] = 0x10325476;
		sum->sha256[4] = 0x42424242;
		r->bsz = 64;//?
	}
	r->len = 0;
	r->size = 0;
}

void read_stdin(uint32_t opts)
{
	uint8_t		buf[SIZE_BUF];
	t_read		r;
	t_chksum	sum;

	ft_printf("------------------------------- EXEC ON STDIN --------------------------------------\n");
	init_chksum(&sum, opts, &r);
	r.buf = buf;
	ft_bzero(r.buf, r.bsz);
	while ((r.len = read(STDIN_FILENO, &r.buf[r.size % r.bsz],
										r.bsz - (r.size % r.bsz))) > 0)
		if (!((r.size += r.len) % r.bsz))
		{
			md5((uint32_t *)r.buf, &sum);
			ft_bzero(r.buf, r.bsz);
		}
	if (!r.size)
		r.size = r.len;
	r.len = r.size % r.bsz;
	format_last_string(&r, opts, &sum);
	return ;
}

void 	read_file(int fd, t_chksum	*sum, t_read *r, uint32_t opts)
{
	ft_bzero(r->buf, r->bsz);
	while ((r->len = read(fd, r->buf, r->bsz)) == (int)(r->bsz))
	{
		md5((uint32_t *)r->buf, sum);
		ft_bzero(r->buf, r->bsz);
		r->size += r->bsz;
	}
	r->size += r->len;
	format_last_string(r, opts, sum);
}

int 	open_file(char *file_name)
{
	struct	stat buf;
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		ft_printf("%s: No such file or directory\n", file_name);
	else if (fstat(fd, &buf) != 0)
		ft_printf("%s: 1222 No such file or directory\n", file_name);
	else if (S_ISDIR(buf.st_mode))
		ft_printf("ft_md5 %s: is a directory\n", file_name);
	else
		return (fd);
	if (fd > -1)
		close (fd);
	return (-1);
}

int process_file(char *file_name, uint32_t opts)
{
	t_read		r;
	int			fd;
	uint8_t		buf[SIZE_BUF];
	t_chksum	sum;

	init_chksum(&sum, opts, &r);
	r.buf = buf;
	ft_printf("------------------ EXEC ON FILE --------------------------\n");
	if ((fd = open_file(file_name)) < 0)
		return (-1);
	read_file(fd, &sum, &r, opts);
	close(fd);
	return (0);
}
