/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:11:17 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/25 07:42:56 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int i = 0;

static inline void	memsetpart64(uint64_t **s, uint64_t c, uint64_t *n)
{
	// if (!i++)
	// 	printf("memset 64\n");
	(*n) -= sizeof(uint64_t);
	*(*s)++ = c;
	// ((c & 0xFF) | (c & 0xFF) << 8 | (c & 0xFF) << 16
	// | (c & 0xFF) << 24 | (c & 0xFF) << 32 | (c & 0xFF) << 40
	// | (c & 0xFF) << 48 | (c & 0xFF) << 56);
}

static inline void	memsetpart32(uint32_t **s, uint32_t c, uint32_t *n)
{
	// printf("memset 32\n");
	(*n) -= sizeof(uint32_t);
	*(*s)++ = c;
	// ((c & 0xFF) | (c & 0xFF) << 8 | (c & 0xFF) << 16
	// | (c & 0xFF) << 24);
}

static inline void	memsetpart16(uint16_t **s, uint16_t c, uint16_t *n)
{
	// printf("memset 16\n");
	(*n) -= sizeof(uint16_t);
	*(*s)++ = c;
	// ((c & 0xFF) | ((c & 0xFF) << 8));
}

static inline void	memsetpart8(uint8_t **s, uint8_t c, uint8_t *n)
{
	// printf("memset 8\n");
	(*n)--;
	*(*s)++ = c;
}

void				*ft_memset(void *s, int c, size_t n)
{
	uint8_t		*ptr;
	uint64_t	c2;

	ptr = s;
	while ((int)ptr % 16 && n)
	{
		*(uint8_t *)ptr++ = (uint8_t)c;
		n--;
	}
	c2 = 0;
	*((uint8_t *)&c2) |= c;
	c2 |= (c2 << 8);
	c2 |= (c2 << 16);
	c2 |= (c2 << 32);
	while (n >= sizeof(uint64_t))
		memsetpart64((uint64_t **)&ptr, c2, (uint64_t *)&n);
	while (n >= sizeof(uint32_t))
		memsetpart32((uint32_t **)&ptr, c2, (uint32_t *)&n);
	while (n >= sizeof(uint16_t))
		memsetpart16((uint16_t **)&ptr, c2, (uint16_t *)&n);
	while (n >= sizeof(uint8_t))
		memsetpart8((uint8_t **)&ptr, c2, (uint8_t *)&n);
	return (s);
}
