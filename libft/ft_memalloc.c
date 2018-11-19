/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 12:10:31 by nboulaye          #+#    #+#             */
/*   Updated: 2015/12/02 23:40:49 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void				*ft_memalloc(size_t size)
{
	unsigned char	*s;

	if (!(s = (unsigned char *)malloc(sizeof(char) * size)))
		return (NULL);
	while (size--)
		s[size] = 0;
	return ((void *)s);
}
