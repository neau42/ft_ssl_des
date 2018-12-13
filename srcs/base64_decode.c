/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/13 02:59:46 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void flush_chunk(t_base64 *base, uint8_t *val, int *i, int *iter)
{
	if (*i > 0)
	{
		// ft_printf("call write: len: %d \n", *i);
		write(base->fd_o, val, *i);
	}	
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
		flush_chunk(base, val, &index, &iter);
	else if ((iter % 4) == 3)
	{
		val[index++] += idx;
		iter++;
		if (index >= 47)
			flush_chunk(base, val, &index, &iter);
	}
	else if ((iter % 4) == 2)
	{
		val[index] += ((idx & 0x3C) >> 2);
		val[++index] = ((idx & 0x3) << 6);
		iter++;
	}
	else if ((iter % 4) == 1)
	{
		val[index] += ((idx & 0x30) >> 4);
		val[++index] = ((idx & 0xF) << 4);
		iter++;
	}
	else if ((iter % 4) == 0)
	{
		val[index] = (idx << 2);
		iter++;
	}
}

void		parse_chunk(t_base64 *base, char *tab, char *buf)
{
	int		i;
	char *ptr;


	i = 0;
	if (ft_strlen(buf) % 4)
	{
		// ft_printf("ERROR: ft_strlen(buf): %d\n", ft_strlen(buf));
		return ;
	}
	while (buf[i])
	{
		if (buf[i] == '=')
		{
			get_b64_decode_value(base, 0, 1);
			break ;
		}
		else if ((ptr = ft_strchr(tab, buf[i])))
			get_b64_decode_value(base, ptr - tab, 0);
		else
			break ;
		i++;
	}
	if (i && !buf[i])
		get_b64_decode_value(base, 0, 1);
}

static int format_chunk(char *tab, char *buf, int len, char *chunk)
{
	int			i;
	static int	j = 0;

	i = 0;
	j = (j % 64);
	while (i < len)
	{
		if (ft_isspace(buf[i]))
			;
		else if (!(ft_strchr(tab, buf[i])) && buf[i] != '=')
			return (0);
		else
			chunk[j++] = buf[i];
		i++;
	}
	// ft_printf("Chunk '%s' (len: %d)\n", chunk, j);
	return (j);
}

void		b64_decode(char *tab, t_base64 *base)
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
		if ((len = format_chunk(tab, read_buf, buf_size, chunk)) == 0)
		{
			len = 0;
			// ft_printf("chunk: '%s'\n", chunk);
			ft_bzero(chunk, B64_DEC_BUF_SIZE + 1);
			continue ;
		}
		else if (len == 64)
		{
			parse_chunk(base, tab, chunk);
			ft_bzero(chunk, B64_DEC_BUF_SIZE + 1);
			len = 0;
		}
		ft_bzero(read_buf, buf_size);
	}
	// ft_printf("chunk: '%s'(%d)\n", chunk, len);
	parse_chunk(base, tab, chunk);
}
