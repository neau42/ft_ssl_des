/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/24 15:27:01 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
extern int errno;

void			set_size_in_chunk(t_read *r, uint32_t opts)
{
	if ((opts & GET_HASH) == OPT_SHA256)
		*(uint64_t *)&r->buf[r->bsz - sizeof(uint64_t)] = endian_swap64(r->size);
	else if ((opts & GET_HASH) == OPT_MD5)
		*(uint64_t *)&r->buf[r->bsz - sizeof(uint64_t)] = r->size;
}

void		format_last_chunk(t_read *r, uint32_t opts, t_chksum *sum)
{
	int add_bit;

	add_bit = 0;
	// ft_printf("\033[93mr->len: %d r->bsz : %d 0000\033[0m\n",r->len, r->bsz);
	if (r->len >= r->bsz)
	{
		algo((uint32_t *)r->buf, sum, opts);
		ft_bzero(r->buf, r->bsz);
		// ft_printf("\033[93mr->len: %d r->bsz : %d 22222\033[0m\n",r->len, r->bsz);
		r->len = 0;
		r->buf[0] = (1 << 7);
	}


	else if (r->len > (int)(r->bsz - (sizeof(uint64_t) + 1)))
	{
		r->buf[r->len] = (1 << 7);
		algo((uint32_t *)r->buf, sum, opts);
		ft_bzero(r->buf, r->bsz);
		// ft_printf("\033[93mr->len: %d r->bsz : %d 22222\033[0m\n",r->len, r->bsz);
		r->len = 0;
	}
	else
		r->buf[r->len] = (1 << 7);

	// if (r->len < r->bsz && ++add_bit)
	// 	r->buf[r->len] = (1 << 7);
	// if (r->len > (int)(r->bsz - sizeof(uint64_t) - 1))
	// {
	// 	algo((uint32_t *)r->buf, sum, opts);
	// 	ft_bzero(r->buf, r->bsz);
	// 	ft_printf("\033[93mr->len: %d r->bsz : %d 22222\033[0m\n",r->len, r->bsz);
	// 	if (!add_bit && r->len == r->bsz - sizeof(uint64_t))
	// 	{
	// 		r->buf[0] = (1 << 7);
	// 	}
	// }
	// else if (r->len == 0 || r->len >= r->bsz)
	// {
	// 	ft_printf("\033[93mr->len: %d r->bsz : %d 33333\033[0m\n",r->len, r->bsz);
	// 	ft_bzero(r->buf, r->bsz);
	// 	r->len = 0;
	// 	r->buf[0] = (1 << 7);
	// }
	set_size_in_chunk(r, opts);
}

static int	read_file(char *file_name, int fd, t_chksum *sum, t_read *r,
						uint32_t opts)
{
	while ((r->len = read(fd, r->buf, r->bsz)) == (int)(r->bsz))
	{
		algo((uint32_t *)r->buf, sum, opts);
		ft_bzero(r->buf, r->bsz);
		r->size += (r->bsz * 8);
	}
	if ((errno)
	&& ft_fdprintf(2, "ft_ssl: %s: %s\n", file_name, strerror(errno)))
		return 1;
	r->size += (r->len * 8);
	format_last_chunk(r, opts, sum);
	return (0);
}

static int	open_file(char *file_name)
{
	struct stat	buf;
	int			fd;

	errno = 0;
	if ((fd = open(file_name, O_RDONLY)) < 0 || errno)
		ft_fdprintf(2, "%s: %s\n", file_name, strerror(errno));
	else if (fstat(fd, &buf))
		ft_fdprintf(2, "%s: No such file or directory\n", file_name);
	else if (S_ISDIR(buf.st_mode))
		ft_fdprintf(2, "ft_md5 %s: is a directory\n", file_name);
	else
		return (fd);
	if (fd > -1)
		close(fd);
	return (-1);
}

int			process_file(char *file_name, uint32_t opts)
{
	t_read		r;
	int			fd;
	uint8_t		buf[SIZE_BUF];
	t_chksum	sum;

	init_chksum_n_read(&sum, opts, &r, (uint8_t *)&buf);
	r.buf = buf;
	r.file_name = file_name;
	if ((fd = open_file(file_name)) < 0)
		return (-1);
	if (read_file(file_name, fd, &sum, &r, opts))
	{
		close(fd);
		return (1);
	}
	close(fd);
	algo((uint32_t *)r.buf, &sum, opts);
	print_chksum(&sum, r.file_name, opts);
	return (0);
}
