/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/15 18:25:16 by nboulaye         ###   ########.fr       */
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

t_chksum	process_string(t_arg *arg, uint32_t opts, uint8_t print)
{
	uint8_t		buf[MD_BUF_SIZE];
	t_read		r;
	t_chksum	sum;
	char		*final_name;
	char		*str;

	str = arg->str;
	init_chksum_n_read(&sum, opts, &r, (uint8_t *)buf);
	while ((r.len = ft_strlen(&str[r.size])) > MD_BUF_SIZE)
	{
		ft_memcpy(r.buf, &str[r.size], MD_BUF_SIZE);
		algo(r.buf, &sum, opts);
		ft_bzero(r.buf, r.bsz);
		r.size += MD_BUF_SIZE;
	}
	ft_memcpy(r.buf, &str[r.size], r.len);
	r.size = ((r.size + r.len) * 8);
	format_last_chunk(&r, opts, &sum);
	algo(r.buf, &sum, opts);
	final_name = format_final_name(str, r.size / 8);
	if (print)
		print_chksum(&sum, final_name, opts);
	if (final_name)
		free(final_name);
	return (sum);
}

t_chksum	process_string_custom(t_arg *arg, uint32_t opts, int len)
{
	uint8_t buf[MD_BUF_SIZE];
	t_read r;
	t_chksum sum;
	char *str;

	str = arg->str;
	init_chksum_n_read(&sum, opts, &r, (uint8_t *)buf);
	r.len = len;
	while (r.len > MD_BUF_SIZE)
	{
		ft_memcpy(r.buf, str, MD_BUF_SIZE);
		algo(r.buf, &sum, opts);
		ft_bzero(r.buf, r.bsz);
		r.size += MD_BUF_SIZE;
		r.len -= MD_BUF_SIZE;
		str += MD_BUF_SIZE;
	}
	ft_memcpy(r.buf, str, r.len);
	r.size = ((r.size + r.len) * 8);
	format_last_chunk(&r, opts, &sum);
	algo(r.buf, &sum, opts);
	return (sum);
}
