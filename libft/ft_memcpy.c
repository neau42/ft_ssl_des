/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:24:10 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 23:56:11 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	memsetpart64(uint64_t **src, uint64_t **dst, uint64_t *n)
{
	(*n) -= sizeof(uint64_t);
	*((*src)++) = *((*dst)++);
}

static void	memsetpart32(uint32_t **src, uint32_t **dst, uint32_t *n)
{
	(*n) -= sizeof(uint32_t);
	*((*src)++) = *((*dst)++);
}

static void	memsetpart16(uint16_t **src, uint16_t **dst, uint16_t *n)
{
	(*n) -= sizeof(uint16_t);
	*((*src)++) = *((*dst)++);
}

static void	memsetpart8(uint8_t **src, uint8_t **dst, uint32_t *n)
{
	(*n)--;
	*((*src)++) = *((*dst)++);
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ret;

	ret = dst;
	while (n >= sizeof(uint64_t))
		memsetpart64((uint64_t **)&dst, (uint64_t **)&src, (uint64_t *)&n);
	while (n >= sizeof(uint32_t))
		memsetpart32((uint32_t **)&dst, (uint32_t **)&src, (uint32_t *)&n);
	while (n >= sizeof(uint16_t))
		memsetpart16((uint16_t **)&dst, (uint16_t **)&src, (uint16_t *)&n);
	while (n >= sizeof(uint8_t))
		memsetpart8((uint8_t **)&dst, (uint8_t **)&src, (uint32_t *)&n);
	return (ret);
}
