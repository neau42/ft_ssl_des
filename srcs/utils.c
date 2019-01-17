/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/17 18:43:17 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	r_rot(uint32_t n, unsigned int c)
{
	unsigned int mask;

	mask = (8 * sizeof(n) - 1);
	c &= mask;
	return (n >> c) | (n << (-c & mask));
}

uint32_t	l_rot28(uint32_t n, unsigned int c)
{
	return (((n << c) | (n >> ((sizeof(n) * 7) - c))) & 0xFFFFFFF);
}

uint32_t	l_rot(uint32_t n, unsigned int c)
{
	return (n << c) | (n >> ((sizeof(n) * CHAR_BIT) - c));
}

static void	print_last_memory_hex(size_t len, size_t size, size_t size2,
					unsigned char *str)
{
	int i;

	i = len;
	while (i--)
		ft_printf("   ");
	while (size2 < size)
	{
		ft_printf("%c", ((ft_isprint(str[size2])) ? str[size2] : '.'));
		size2++;
	}
	i = len;
	while (i--)
		ft_printf(" ");
	ft_printf("|\n");
}

void		print_memory_hex(void *data, size_t blk_size)
{
	size_t			size;
	size_t			size2;
	unsigned char	*str;

	str = data;
	size = 0;
	size2 = 0;
	ft_printf("\n|\t");
	while (size < blk_size)
	{
		if (size % 4 == 0)
			ft_printf("(%.3d) ", size / 4);
		ft_printf("%  4p:%08b ", str[size], str[size]);
		if (++size % 4 == 0)
		{
			while (size2 < size)
			{
				ft_printf("%c", ((ft_isprint(str[size2])) ? str[size2] : '.'));
				size2++;
			}
			if (size2 < blk_size)
				ft_printf("|\n|\t");
		}
	}
	print_last_memory_hex(size - size2, size, size2, str);
}
