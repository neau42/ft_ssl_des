/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:11:17 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/20 08:19:15 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
# include <inttypes.h>


void				*ft_memset(void *s, int c, size_t n)
{
	void *ret = s;

	while (n >= sizeof(uint32_t))
	{
		n -= sizeof(uint32_t);
		*((uint32_t *)s) = ((unsigned char)c | (unsigned char)c << 8
						| (unsigned char)c << 16 | (unsigned char)c << 24);
		s += sizeof(uint32_t);
	}
	while (n >= sizeof(uint16_t))
	{
		n -= sizeof(uint16_t);
		*((uint16_t *)s) = ((unsigned char)c | ((unsigned char)c << 8));
		s += sizeof(uint16_t);
	}
	while (n >= sizeof(uint8_t))
	{
		n -= sizeof(uint8_t);
		*((unsigned char *)s) = (unsigned char)c;
		s += sizeof(uint8_t);
	}
	return (ret);
}
