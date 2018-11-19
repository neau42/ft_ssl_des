/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:24:02 by nboulaye          #+#    #+#             */
/*   Updated: 2015/12/22 14:44:05 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t			i;

	i = 0;
	while (*src && n)
	{
		dst[i] = *src;
		i++;
		src++;
		n--;
	}
	while (n)
	{
		dst[i] = '\0';
		i++;
		n--;
	}
	return (dst);
}
