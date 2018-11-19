/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 00:09:10 by nboulaye          #+#    #+#             */
/*   Updated: 2016/05/15 00:13:38 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t		wc(const char *s, char c)
{
	size_t			nbrwd;

	nbrwd = 0;
	while (*s)
	{
		while (*s == c)
			s += 1;
		if (*s && *s != c)
			nbrwd++;
		while (*s && *s != c)
			s += 1;
	}
	return (nbrwd);
}

char				**ft_strsplit(const char *s, char c)
{
	char			**r;
	size_t			len;
	size_t			n;

	if (!(n = 0) && (!s || !c ||
				!(r = (char **)ft_memalloc(sizeof(char *) * (wc(s, c) + 1)))))
		return (NULL);
	while (*s && (++n) && !(len = 0))
	{
		while (*s && *(char *)s == c)
			s += 1;
		while (s[len] && ((char *)s)[len] != c)
			len++;
		if (*s)
		{
			if (!(r[n - 1] = ft_strnew(len)))
				return (NULL);
			ft_strncpy(r[n - 1], s, len);
		}
		s += len;
	}
	return (r);
}
