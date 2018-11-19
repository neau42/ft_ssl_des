/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:10:31 by nboulaye          #+#    #+#             */
/*   Updated: 2016/06/27 17:48:19 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strrchr(const char *s, int c)
{
	size_t		len;

	len = ft_strlen(s) + 1;
	while (len--)
		if (s[len] == (char)c)
			return ((char *)&s[len]);
	return (NULL);
}
