/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:11:17 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 23:57:59 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	memsetpart64(uint64_t **s, uint64_t c, uint64_t *n)
{
	(*n) -= sizeof(uint64_t);
	*(*s)++ = ((c & 0xFF) | (c & 0xFF) << 8 | (c & 0xFF) << 16
	| (c & 0xFF) << 24 | (c & 0xFF) << 32 | (c & 0xFF) << 40
	| (c & 0xFF) << 48 | (c & 0xFF) << 56);
}

static void	memsetpart32(uint32_t **s, uint32_t c, uint32_t *n)
{
	(*n) -= sizeof(uint32_t);
	*(*s)++ = ((c & 0xFF) | (c & 0xFF) << 8 | (c & 0xFF) << 16
	| (c & 0xFF) << 24);
}

static void	memsetpart16(uint16_t **s, uint16_t c, uint16_t *n)
{
	(*n) -= sizeof(uint16_t);
	*(*s)++ = ((c & 0xFF) | ((c & 0xFF) << 8));
}

static void	memsetpart8(uint8_t **s, uint8_t c, uint32_t *n)
{
	(*n)--;
	*(*s)++ = (c & 0xFF);
}

void		*ft_memset(void *s, uint64_t c, size_t n)
{
	void	*ret;

	ret = s;
	while (n >= sizeof(uint64_t))
		memsetpart64((uint64_t **)&s, c, (uint64_t *)&n);
	while (n >= sizeof(uint32_t))
		memsetpart32((uint32_t **)&s, c, (uint32_t *)&n);
	while (n >= sizeof(uint16_t))
		memsetpart16((uint16_t **)&s, c, (uint16_t *)&n);
	while (n >= sizeof(uint8_t))
		memsetpart8((uint8_t **)&s, c, (uint32_t *)&n);
	return (ret);
}
