/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 21:35:34 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		read_stdin(uint32_t opts)
{
	uint8_t buf[SIZE_BUF];
	t_read r;
	t_chksum sum;

	// ft_printf("------------- EXEC ON STDIN --------------------\n");
	if (read(STDIN_FILENO, buf, 0) < 0)
		return;

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
	algo((uint32_t *)r.buf, &sum, opts);
	print_chksum(&sum, r.file_name, opts);
	return;
}

int			process_null(char *str, uint32_t opts)
{
	(void)str;
	if (!(opts & OPT_FILE) || opts & OPT_P)
		read_stdin(opts);
	return (0);
}
