/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/24 06:02:40 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*format_final_name(char *str, uint64_t size)
{
	char	*final_name;

	if (!(final_name = ft_strnew(size + 2)))
		return (NULL);
	ft_strcpy(final_name, "\"");
	ft_strcat(final_name, str);
	ft_strcat(final_name, "\"");
	return (final_name);
}

int		process_string(char *str, uint32_t opts)
{
	uint8_t		buf[SIZE_BUF];
	t_read		r;
	t_chksum	sum;
	char		*final_name;

	init_chksum_n_read(&sum, opts, &r, (uint8_t *)buf);
	while ((r.len = ft_strlen(&str[r.size])) > SIZE_BUF)
	{
		ft_memcpy(r.buf, &str[r.size], SIZE_BUF);
		algo(r.buf, &sum, opts);
		ft_bzero(r.buf, r.bsz);
		r.size += SIZE_BUF;
	}
	ft_memcpy(r.buf, &str[r.size], r.len);
	r.size = ((r.size + r.len) * 8);
	format_last_chunk(&r, opts, &sum);
	algo(r.buf, &sum, opts);
	final_name = format_final_name(str, r.size / 8);
	print_chksum(&sum, final_name, opts);
	if (final_name)
		free(final_name);
	return (0);
}
