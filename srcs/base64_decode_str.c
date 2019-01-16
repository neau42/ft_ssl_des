/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/16 15:27:59 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	flush_chunk(char *buf_out, uint8_t *val, int *iter)
{
	if (iter[1] > 0)
	{
		while (*buf_out)
			buf_out++;
		ft_memcpy(buf_out, (char *)val, iter[1]);
	}
	ft_bzero(val, sizeof(uint8_t) * iter[1]);
	iter[1] = 0;
	iter[0] = 0;
}

static void	get_b64_decode_value(char *buf_out, uint8_t idx, int op)
{
	static uint8_t	val[48] = {0};
	static int		iter[2] = {0};

	if (op)
		return (flush_chunk(buf_out, val, iter));
	else if ((iter[0] % 4) == 3)
	{
		val[iter[1]++] += idx;
		if (iter[1] >= 47)
			return (flush_chunk(buf_out, val, iter));
	}
	else if ((iter[0] % 4) == 2)
	{
		val[iter[1]] += ((idx & 0x3C) >> 2);
		val[++iter[1]] = ((idx & 0x3) << 6);
	}
	else if ((iter[0] % 4) == 1)
	{
		val[iter[1]] += ((idx & 0x30) >> 4);
		val[++iter[1]] = ((idx & 0xF) << 4);
	}
	else if ((iter[0] % 4) == 0)
		val[iter[1]] = (idx << 2);
	iter[0]++;
}

void		b64_decode_str(char *buf_in, char *buf_out, size_t size)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (i < size && buf_in[i])
	{
		if (buf_in[i] == '=')
		{
			get_b64_decode_value(buf_out, 0, 1);
			break ;
		}
		else if ((ptr = ft_strchr(g_b64, buf_in[i])))
			get_b64_decode_value(buf_out, ptr - g_b64, 0);
		else
			break ;
		i++;
	}
	if (i && !buf_in[i])
		get_b64_decode_value(buf_out, 0, 1);
}
