/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:37:19 by nboulaye          #+#    #+#             */
/*   Updated: 2016/06/29 19:54:17 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;

	i = 0;
	if (!len || dst == src)
		return (dst);
	if (dst < src)
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	else
	{
		while (len--)
			((char *)dst)[len] = ((char *)src)[len];
		((char *)dst)[0] = ((char *)src)[0];
	}
	return (dst);
}
