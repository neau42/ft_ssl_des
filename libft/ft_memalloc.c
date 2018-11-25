/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 12:10:31 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/24 21:51:34 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void				*ft_memalloc(size_t size)
{
	unsigned char	*s;

	if (!(s = (unsigned char *)malloc(sizeof(char) * size)))
		return (NULL);
	ft_bzero(s, size);
	return ((void *)s);
}
