/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 18:12:20 by no               ###   ########.fr       */
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
	int test = 0;

	(void)opts;
	if (r->len < r->bsz && ++test)
		r->buf[r->len] = (1 << 7);
	if (r->len > (int)(r->bsz - sizeof(uint64_t) - 1))
	{
		algo((uint32_t *)r->buf, sum, opts);
		ft_bzero(r->buf, r->bsz);
		if (!test && r->len == r->bsz - sizeof(uint64_t))
			r->buf[0] = (1 << 7);
	}
	else if (r->len == 0 || r->len >= r->bsz)
	{
		ft_bzero(r->buf, r->bsz);
		r->len = 0;
		// if (!test)
		r->buf[0] = (1 << 7);
	}
	*(uint64_t *)&r->buf[r->bsz - sizeof(uint64_t)] = (r->size);
	// ft_printf("\033[94m(r->size): %d\n\033[0m",(r->size));
	algo((uint32_t *)r->buf, sum,opts);
	print_chksum(sum, r->file_name, opts);
}

void init_chksum_n_read(t_chksum *sum, uint32_t opts, t_read *r)
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

void read_stdin(uint32_t opts)
{
	uint8_t		buf[SIZE_BUF];
	t_read		r;
	t_chksum	sum;

	ft_printf("------------------------------- EXEC ON STDIN --------------------------------------\n");
	init_chksum_n_read(&sum, opts, &r);
	r.buf = buf;
	ft_bzero(r.buf, r.bsz);
	while ((r.len = read(STDIN_FILENO, &r.buf[r.size % r.bsz],
										r.bsz - (r.size % r.bsz))) > 0)
		if (!((r.size += r.len) % r.bsz))
		{
			algo((uint32_t *)r.buf, &sum, opts);
			ft_bzero(r.buf, r.bsz);
		}
	if (!r.size)
		r.size = r.len;
	r.len = r.size % r.bsz;
	r.size *= 8;
	format_last_string(&r, opts, &sum);
	return ;
}

void 	read_file(int fd, t_chksum	*sum, t_read *r, uint32_t opts)
{
	ft_bzero(r->buf, r->bsz);
	while ((r->len = read(fd, r->buf, r->bsz)) == (int)(r->bsz))
	{
		algo((uint32_t *)r->buf, sum, opts);
		ft_bzero(r->buf, r->bsz);
		r->size += (r->bsz * 8);
	}
	r->size += (r->len * 8);
	format_last_string(r, opts, sum);
}

int 	open_file(char *file_name)
{
	struct stat	buf;
	int			fd;

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

	init_chksum_n_read(&sum, opts, &r);
	r.buf = buf;
	r.file_name = file_name;
	// ft_printf("------------------ EXEC ON FILE --------------------------\n");
	if ((fd = open_file(file_name)) < 0)
		return (-1);
	read_file(fd, &sum, &r, opts);
	close(fd);
	return (0);
}
