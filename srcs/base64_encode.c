/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/01 09:21:14 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	get_b64_value(char *val, uint8_t *buf, int test, int len)
{
	if (len - test > 2)
	{
		val[0] = (buf[test] >> 2);
		val[1] = (((buf[test] & 0x3) << 4) + (buf[test + 1] >> 4));
		val[2] = (((buf[test + 1] & 0x0F) << 2) + (buf[test + 2] >> 6));
		val[3] = buf[test + 2] & 0x3F;
	}
	else if (len - test > 1)
	{
		val[0] = (buf[test] >> 2);
		val[1] = (((buf[test] & 0x3) << 4) + (buf[test + 1] >> 4));
		val[2] = ((buf[test + 1] & 0x0F) << 2);

	}
	else if (len - test > 0)
	{
		val[0] = (buf[test] >> 2);
		val[1] = ((buf[test] & 0x3) << 4);
	}
}

static void	b64_ecode_last_block(t_base64 *base, char *tab, char *val, int len)
{
	int		size;
	int		i;

	if (!(size = len % 3))
		size = 3;
	i = -1;
	while (++i < (size + 1))
		ft_fdprintf(base->fd_o, "%c", tab[(int)val[i]]);
	while (size % 3)
	{
		ft_fdprintf(base->fd_o, "=");
		size++;
	}
}

static void	b64_encode_buffer(t_base64 *base, char *buf, int len, char *tab)
{
	char	val[4];
	int		i;
	int		test;

	test = 0;
	ft_bzero(val, 4);
	while (test < len - 3)
	{
		get_b64_value(val, (uint8_t *)buf, test, len);
		i = -1;
		while (++i < 4)
			ft_fdprintf(base->fd_o, "%c", tab[(int)val[i]]);
		test += 3;
	}
	get_b64_value(val, (uint8_t *)buf, test, len);
	b64_ecode_last_block(base, tab, val, len);
	ft_printf("\n");
	ft_bzero((uint8_t *)buf, B64_ENC_BUF_SIZE);
}

void		b64_encode(char *tab, t_base64 *base)
{
	char buf[B64_ENC_BUF_SIZE];
	int buf_size;
	int len;

	len = 0;
	ft_bzero(buf, B64_ENC_BUF_SIZE);
	while ((buf_size = read(base->fd_i, &buf, B64_ENC_BUF_SIZE)) > 0)
		b64_encode_buffer(base, buf, buf_size, tab);
}