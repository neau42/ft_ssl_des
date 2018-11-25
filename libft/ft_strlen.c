/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 18:44:43 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/25 03:57:54 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <sys/types.h>
#include <string.h>

static ssize_t	get_zero(const char *p, const char *str)
{
	if (!p[0])
		return (p - str + 0);
	if (!p[1])
		return (p - str + 1);
	if (!p[2])
		return (p - str + 2);
	if (!p[3])
		return (p - str + 3);
	if (!p[4])
		return (p - str + 4);
	if (!p[5])
		return (p - str + 5);
	if (!p[6])
		return (p - str + 6);
	if (!p[7])
		return (p - str + 7);
	return (-1);
}

size_t			ft_strlen(const char *str)
{
	const char		*p;
	const uint64_t	*lp;
	ssize_t			len;

	p = str;
	while ((uint64_t)p & (sizeof(uint64_t) - 1))
		if (!*p)
			return (p - str);
		else
			p++;
	lp = (const uint64_t *)p;
	while (42)
	{
		if ((*lp - 0x0101010101010101) & 0x8080808080808080
		&& (len = get_zero((const char *)(lp), str)) != -1)
			return ((size_t)len);
		lp++;
	}
	return (0);
}
