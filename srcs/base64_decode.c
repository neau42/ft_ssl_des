/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/03 10:35:19 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_n_init_static(t_base64 *base, uint8_t *val, int *i)
{
	if (*i == 1)
		write(base->fd_o, val, 1);
	else if (*i == 2)
		write(base->fd_o, val, 2);
	else if (*i == 3)
		write(base->fd_o, val, 3);
	*i = 0;
	val[0] = 0;
	val[1] = 0;
	val[2] = 0;
}

static void	get_b64_decode_value(t_base64 *base, uint8_t idx, int op)
{
	static uint8_t	val[3] = {0};
	static int		i = 0;

	if (op)
	{
		i -= 1;
		print_n_init_static(base, val, &i);
	}
	else if (i == 3)
	{
		val[2] += idx;
		print_n_init_static(base, val, &i);
	}
	else if (i == 2)
	{
		val[1] += ((idx & 0x3C) >> 2);
		val[i++] = ((idx & 0x3) << 6);
	}
	else if (i == 1)
	{
		val[0] += ((idx & 0x30) >> 4);
		val[i++] = ((idx & 0xF) << 4);
	}
	else if (i == 0)
		val[i++] = (idx << 2);
}

static int	get_one_chars(t_base64 *base, char c, char *tab)
{
	char			*ptr;

	if (!c)
		return (1);
	else if (ft_isspace(c))
		;
	else if (c == '=')
	{
		get_b64_decode_value(base, 0, 1);
		return (1);
	}
	else if ((ptr = ft_strchr(tab, c)))
		get_b64_decode_value(base, ptr - tab, 0);
	else
		return (1);
	return (0);
}

static int	valid_chunk(char *buf, int *len, char *tab)
{
	int		i;
	char	*ptr;

	i = -1;
	while (++i < *len)
	{
		if (ft_isspace(buf[i]) || buf[i] == '=')
			;
		else if (!(ptr = ft_strchr(tab, buf[i])))
			return (0);
	}
	return (1);
}

void		b64_decode(char *tab, t_base64 *base)
{
	char	buf[B64_DEC_BUF_SIZE];
	int		buf_size;
	int		len;
	int		i;

	len = 0;
	ft_bzero(buf, B64_DEC_BUF_SIZE);
	while ((buf_size = read(base->fd_i, &buf, B64_DEC_BUF_SIZE)) > 0)
	{
		i = 0;
		if (valid_chunk(buf, &buf_size, tab))
			while (i < buf_size)
			{
				if (get_one_chars(base, buf[i], tab))
					break ;
				i++;
			}
		ft_bzero(buf, 4);
		i++;
	}
}
