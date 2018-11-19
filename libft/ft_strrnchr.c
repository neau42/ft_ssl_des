/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrnchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:10:31 by nboulaye          #+#    #+#             */
/*   Updated: 2016/06/27 17:48:16 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrnchr(const char *s, int c, size_t max)
{
	size_t	len;

	len = ft_strlen(s) + 1;
	if (len > max)
		len = max;
	while (len--)
		if (s[len] == (char)c)
			return ((char *)&s[len]);
	return (NULL);
}
