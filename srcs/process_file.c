/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 21:21:56 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		format_last_string(t_read *r, uint32_t opts, t_chksum *sum)
{
	int add_bit;

	add_bit = 0;
	if (r->len < r->bsz && ++add_bit)
		r->buf[r->len] = (1 << 7);
	if (r->len > (int)(r->bsz - sizeof(uint64_t) - 1))
	{
		algo((uint32_t *)r->buf, sum, opts);
		ft_bzero(r->buf, r->bsz);
		if (!add_bit && r->len == r->bsz - sizeof(uint64_t))
			r->buf[0] = (1 << 7);
	}
	else if (r->len == 0 || r->len >= r->bsz)
	{
		ft_bzero(r->buf, r->bsz);
		r->len = 0;
		r->buf[0] = (1 << 7);
	}
	*(uint64_t *)&r->buf[r->bsz - sizeof(uint64_t)] = (r->size);
}

static void	read_file(int fd, t_chksum	*sum, t_read *r, uint32_t opts)
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

static int open_file(char *file_name)
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

int		process_file(char *file_name, uint32_t opts)
{
	t_read		r;
	int			fd;
	uint8_t		buf[SIZE_BUF];
	t_chksum	sum;

	init_chksum_n_read(&sum, opts, &r);
	r.buf = buf;
	r.file_name = file_name;
	if ((fd = open_file(file_name)) < 0)
		return (-1);
	read_file(fd, &sum, &r, opts);
	close(fd);
	algo((uint32_t *)r.buf, &sum, opts);
	print_chksum(&sum, r.file_name, opts);
	return (0);
}
