/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/14 06:24:19 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern char g_b64[];
// static char g_b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
// 					  "0123456789+/";

static void	flush_chunk(t_base64 *base, uint8_t *val, int *i, int *iter)
{
	if (*i > 0)
		write(base->fd_o, val, *i);
	ft_bzero(val, sizeof(uint8_t) * *i);
	*i = 0;
	*iter = 0;
}

static void	get_b64_decode_value(t_base64 *base, uint8_t idx, int op)
{
	static uint8_t	val[48] = {0};
	static int		iter = 0;
	static int		index = 0;

	if (op)
		return flush_chunk(base, val, &index, &iter);
	else if ((iter % 4) == 3)
	{
		val[index++] += idx;
		if (index >= 47)
			return flush_chunk(base, val, &index, &iter);
	}
	else if ((iter % 4) == 2)
	{
		val[index] += ((idx & 0x3C) >> 2);
		val[++index] = ((idx & 0x3) << 6);
	}
	else if ((iter % 4) == 1)
	{
		val[index] += ((idx & 0x30) >> 4);
		val[++index] = ((idx & 0xF) << 4);
	}
	else if ((iter % 4) == 0)
		val[index] = (idx << 2);
	iter++;
}

static void	parse_chunk(t_base64 *base, char *buf)
{
	int		i;
	char	*ptr;

	i = -1;
	if (ft_strlen(buf) % 4)
		return ;
	while (buf[++i])
		if (buf[i] == '=')
		{
			get_b64_decode_value(base, 0, 1);
			break ;
		}
		else if ((ptr = ft_strchr(g_b64, buf[i])))
			get_b64_decode_value(base, ptr - g_b64, 0);
		else
			break ;
	if (i && !buf[i])
		get_b64_decode_value(base, 0, 1);
}

static int	format_chunk(char *buf, int len, char *chunk)
{
	int			i;
	static int	j = 0;

	i = 0;
	j = (j % 64);
	while (i < len)
	{
		if (ft_isspace(buf[i]))
			;
		else if (!(ft_strchr(g_b64, buf[i])) && buf[i] != '=')
			return (0);
		else
			chunk[j++] = buf[i];
		i++;
	}
	return (j);
}

void		b64_decode(t_base64 *base)
{
	char	read_buf[B64_DEC_BUF_SIZE + 1];
	char	chunk[B64_DEC_BUF_SIZE + 1];
	int		buf_size;
	int		len;

	len = 0;
	ft_bzero(read_buf, B64_DEC_BUF_SIZE + 1);
	ft_bzero(chunk, B64_DEC_BUF_SIZE + 1);
	while ((buf_size = read(base->fd_i, read_buf, B64_DEC_BUF_SIZE - len)) > 0)
	{
		if ((len = format_chunk(read_buf, buf_size, chunk)) == 0)
		{
			len = 0;
			ft_bzero(chunk, B64_DEC_BUF_SIZE + 1);
			continue ;
		}
		else if (len == 64)
		{
			parse_chunk(base, chunk);
			ft_bzero(chunk, B64_DEC_BUF_SIZE + 1);
			len = 0;
		}
		ft_bzero(read_buf, buf_size);
	}
	parse_chunk(base, chunk);
}
