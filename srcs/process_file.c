/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/27 04:41:25 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	set_size_in_chunk(t_read *r, uint32_t opts)
{
	if ((opts & GET_HASH) == OPT_SHA256)
		*(uint64_t *)&r->buf[r->bsz - sizeof(uint64_t)] =
			endian_swap64(r->size);
	else if ((opts & GET_HASH) == OPT_MD5)
		*(uint64_t *)&r->buf[r->bsz - sizeof(uint64_t)] = r->size;
}

void		format_last_chunk(t_read *r, uint32_t opts, t_chksum *sum)
{
	int add_bit;

	add_bit = 0;
	if (r->len >= r->bsz)
	{
		algo((uint32_t *)r->buf, sum, opts);
		ft_bzero(r->buf, r->bsz);
		r->len = 0;
		r->buf[0] = (1 << 7);
	}
	else if (r->len > (int)(r->bsz - (sizeof(uint64_t) + 1)))
	{
		r->buf[r->len] = (1 << 7);
		algo((uint32_t *)r->buf, sum, opts);
		ft_bzero(r->buf, r->bsz);
		r->len = 0;
	}
	else
		r->buf[r->len] = (1 << 7);
	set_size_in_chunk(r, opts);
}

static int	open_file(char *file_name)
{
	struct stat	stat;
	int			fd;

	errno = 0;
	if ((fd = open(file_name, O_RDONLY)) < 0 || errno)
		ft_fdprintf(2, "%s: %s\n", file_name, strerror(errno));
	else if (fstat(fd, &stat))
		ft_fdprintf(2, "%s: No such file or directory\n", file_name);
	else if (S_ISDIR(stat.st_mode))
		ft_fdprintf(2, "ft_md5 %s: is a directory\n", file_name);
	else
		return (fd);
	if (fd > -1)
		close(fd);
	return (-1);
}

static int	read_file(char *file_name, t_chksum *sum, t_read *r, uint32_t opts)
{
	int fd;

	if ((fd = open_file(file_name)) < 0)
		return (-1);
	while ((r->len = read(fd, r->buf, r->bsz)) == (int)(r->bsz))
	{
		algo((uint32_t *)r->buf, sum, opts);
		ft_bzero(r->buf, r->bsz);
		r->size += (r->bsz * 8);
	}
	if ((errno)
	&& ft_fdprintf(2, "ft_ssl: %s: %s\n", file_name, strerror(errno)))
	{
		close(fd);
		return (1);
	}
	r->size += (r->len * 8);
	format_last_chunk(r, opts, sum);
	close(fd);
	return (0);
}

int			process_file(t_arg *arg, uint32_t opts)
{
	t_read		r;
	uint8_t		buf[SIZE_BUF];
	t_chksum	sum;
	char		*file_name;

	file_name = arg->str;
	init_chksum_n_read(&sum, opts, &r, (uint8_t *)&buf);
	r.buf = buf;
	r.file_name = file_name;
	if (read_file(file_name, &sum, &r, opts))
		return (1);
	algo((uint32_t *)r.buf, &sum, opts);
	print_chksum(&sum, r.file_name, opts);
	return (0);
}
