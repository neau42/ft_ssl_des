/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/01 09:23:21 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		read_stdin(uint32_t opts)
{
	uint8_t		buf[MD_BUF_SIZE];
	t_read		r;
	t_chksum	sum;

	init_chksum_n_read(&sum, opts, &r, (uint8_t *)&buf);
	while ((r.len = read(STDIN_FILENO, &r.buf[r.size % r.bsz],
			r.bsz - (r.size % r.bsz))) > 0)
		if (!((r.size += r.len) % r.bsz))
		{
			(opts & OPT_P) ? write(1, r.buf, r.bsz) : 1;
			algo((uint32_t *)r.buf, &sum, opts);
			ft_bzero(r.buf, r.bsz);
		}
	(opts & OPT_P) ? ft_printf((char *)r.buf) : 1;
	if (!r.size)
		r.size = r.len;
	r.len = r.size % r.bsz;
	r.size *= 8;
	format_last_chunk(&r, opts, &sum);
	algo((uint32_t *)r.buf, &sum, opts);
	print_chksum(&sum, r.file_name, opts);
}

int			process_stdin(t_arg *arg, uint32_t opts)
{
	(void)arg;
	if ((read(STDIN_FILENO, NULL, 0) < 0)
	&& ft_fdprintf(2, "Read Error in (stdin)\n"))
		return (1);
	read_stdin(opts);
	return (0);
}
