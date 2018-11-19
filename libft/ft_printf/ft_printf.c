/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@42.fr>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 16:25:34 by nboulaye          #+#    #+#             */
/*   Updated: 2018/05/02 01:21:43 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ret_fd(int fd)
{
	static int	out = 1;

	if (fd >= 0)
		out = fd;
	return (out);
}

int			add_in_buf(t_buf *b, char c)
{
	static int nb_flush = 0;

	if (c == INIT_BUF && !(b->i = 0) &&
		!(nb_flush = 0))
		return (0);
	else if (c == INIT_BUF_SPRINTF && !(b->i = 0) &&
		(nb_flush = -2))
		return (0);
	if (c == -3 && !(b->i = 0))
		nb_flush = -1;
	if (nb_flush == -1)
		return (-1);
	if (c == REINIT_BUF)
		return ((nb_flush = 0));
	if (c == RETURN_NB_FLUSH)
		return (nb_flush);
	if (b->i >= BUF_LEN && nb_flush != -2)
	{
		write(ret_fd(-1), b->buf, BUF_LEN);
		b->i = 0;
		nb_flush++;
	}
	b->buf[b->i++] = c;
	return (-1);
}

int			ft_printf(const char *format, ...)
{
	va_list			pa;
	t_buf			b;
	int				ret;
	static char		buf[BUF_LEN + 4];

	b.buf = buf;
	add_in_buf(&b, INIT_BUF);
	va_start(pa, format);
	while (*format)
	{
		if (*format == '%' && (format++))
			read_next_arg(&b, (char **)(&format), &pa);
		else if (*format)
			add_in_buf(&b, *format);
		if (!*format)
			break ;
		format++;
	}
	va_end(pa);
	write(1, b.buf, b.i);
	ret = b.i + (add_in_buf(&b, RETURN_NB_FLUSH) * BUF_LEN);
	add_in_buf(&b, REINIT_BUF);
	return (ret >= 0) ? ret : -1;
}

int			ft_fdprintf(int fd, const char *format, ...)
{
	va_list			pa;
	t_buf			b;
	int				ret;
	static char		buf[BUF_LEN + 4];

	ret_fd(fd);
	b.buf = buf;
	add_in_buf(&b, INIT_BUF);
	va_start(pa, format);
	while (*format)
	{
		if (*format == '%' && (format++))
			read_next_arg(&b, (char **)(&format), &pa);
		else if (*format)
			add_in_buf(&b, *format);
		if (!*format)
			break ;
		format++;
	}
	va_end(pa);
	write(ret_fd(-1), b.buf, b.i);
	ret = b.i + (add_in_buf(&b, RETURN_NB_FLUSH) * BUF_LEN);
	add_in_buf(&b, REINIT_BUF);
	return (ret >= 0) ? ret : -1;
}

int			ft_sprintf(char *str, const char *format, ...)
{
	va_list			pa;
	t_buf			b;
	int				ret;

	b.buf = str;
	add_in_buf(&b, INIT_BUF_SPRINTF);
	va_start(pa, format);
	while (*format)
	{
		if (*format == '%' && (format++))
			read_next_arg(&b, (char **)(&format), &pa);
		else if (*format)
			add_in_buf(&b, *format);
		if (!*format)
			break ;
		format++;
	}
	va_end(pa);
	b.buf[b.i] = '\0';
	ret = b.i + (add_in_buf(&b, RETURN_NB_FLUSH) * BUF_LEN);
	add_in_buf(&b, REINIT_BUF);
	return (ret >= 0) ? ret : -1;
}
