/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/20 15:37:11 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t    leftrotate (uint64_t x, int offset)
{
	return ( x << offset ) | ( x >> (64 - offset));
}

uint64_t        endian_swap64(uint64_t x)
{
        return (
                ((x & 0x00000000000000FF) << 56)
                + ((x & 0x000000000000FF00) << 40)
                + ((x & 0x0000000000FF0000) << 24)
                + ((x & 0x00000000FF000000) << 8)
                + ((x & 0x000000FF00000000) >> 8)
                + ((x & 0x0000FF0000000000) >> 24)
                + ((x & 0x00FF000000000000) >> 40)
                + ((x & 0xFF00000000000000) >> 56));
}

static void             print_last_memory_hex(size_t len, size_t size, size_t size2,
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
        ft_printf("|");
}

void                    print_memory_hex(void *data, size_t blk_size)
{
        size_t                  size;
        size_t                  size2;
        unsigned char   *str;
        int idx;

        str = data;
        ft_printf("\n|\t");
        size = 0;
        size2 = 0;
        idx = 0;
        while (size < blk_size)
        {
                ft_printf("%08b ", str[size]);
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
        ft_printf("\n");
}
