/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 23:51:34 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		read_stdin(uint32_t opts)
{
	uint8_t		buf[SIZE_BUF];
	t_read		r;
	t_chksum	sum;

	init_chksum_n_read(&sum, opts, &r, (uint8_t *)&buf);
	while ((r.len = read(STDIN_FILENO, &r.buf[r.size % r.bsz],
			r.bsz - (r.size % r.bsz))) > 0)
		if (!((r.size += r.len) % r.bsz))
		{
			!(opts & OPT_Q) ? write(1, r.buf, r.bsz) : 1;
			algo((uint32_t *)r.buf, &sum, opts);
			ft_bzero(r.buf, r.bsz);
		}
	if (!r.size)
		r.size = r.len;
	r.len = r.size % r.bsz;
	r.size *= 8;
	!(opts & OPT_Q) ? ft_printf("%s\n", r.buf) : 1;
	format_last_string(&r, opts, &sum);
	algo((uint32_t *)r.buf, &sum, opts);
	print_chksum(&sum, r.file_name, opts);
}

int			process_stdin(char *str, uint32_t opts)
{
	(void)str;
	if (!(opts & OPT_FILE) || opts & OPT_P)
	{
		if ((read(STDIN_FILENO, NULL, 0) < 0)
		&& ft_fdprintf(2, "Read Error in (stdin)\n"))
			return (1);
		read_stdin(opts);
	}
	return (0);
}
