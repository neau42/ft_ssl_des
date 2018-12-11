/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/11 23:07:27 by nboulaye         ###   ########.fr       */
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
	// else if (ft_isspace(c))
	// 	ft_printf("get_one_chars - ft_isspace NOPE\n");
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

static int format_chunk(char *tab, char *buf, int len)
{
	int i;

	i = 0;
	while (i < len)
		if (ft_isspace(buf[i]))
		{
			ft_memmove(&buf[i], &buf[i + 1], ft_strlen(&buf[i]));
			len--;
		}
		else if (buf[i] == '=')
		{
			if ((i + 1) < len && buf[i + 1] == '=')
			{
				buf[i + 2] = '\0';
				// ft_printf("0 --- i = %d\n", i);
				return (i % 3 == 0) ? (i + 2) : -1;
			}
			buf[i + 1] = '\0';
			// ft_printf("1 --- i = %d\n", i);
			return (((i + 1) % 4) == 0) ? (i + 1) : -1;
		}
		else if (!(ft_strchr(tab, buf[i])))
			return (-1);
		else
			i++;
	return (len);
}

void		parse_chunk(t_base64 *base, char *tab, char *buf)
{
	int		i;

	i = 0;
	while (buf[i])
	{
		if (get_one_chars(base, buf[i], tab))
			break ;
		i++;
	}
}

void		b64_decode(char *tab, t_base64 *base)
{
	char	buf[B64_DEC_BUF_SIZE + 1];
	int		buf_size;
	int		len;

	(void)base;
	len = 0;
	ft_bzero(buf, B64_DEC_BUF_SIZE + 1);
	while ((buf_size = read(base->fd_i, &buf[len], B64_DEC_BUF_SIZE - len)) > 0)
	{
		if ((len = format_chunk(tab, buf, buf_size + len)) == -1)
		{
			len = 0;
			ft_bzero(buf, B64_DEC_BUF_SIZE + 1);
			continue ;
		}
		if (len == 64)
		{
			// ft_printf("buf: '%s' buf_size: %d, len: %d, strlen: %d\n", buf, buf_size, len, ft_strlen(buf));
			parse_chunk(base, tab, buf);
			ft_bzero(buf, B64_DEC_BUF_SIZE + 1);
			len = 0;
		}
	}
	// ft_printf("LAST: buf: '%s' buf_size: %d, len: %d, strlen: %d\n", buf, buf_size, len, ft_strlen(buf));
	parse_chunk(base, tab, buf);
}
		// if (valid_chunk())



		// i = 0;
		// if ((len = valid_chunk(&buf[len], &buf_size, tab, len)) == 64)
		// 	while (i < buf_size)
		// 	{
		// 		if (get_one_chars(base, buf[i], tab))
		// 			break ;
		// 		i++;
		// 	}
		// ft_bzero(buf, 4);
		// i++;
	// }
