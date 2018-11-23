/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 18:44:43 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/23 19:00:16 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *str)
// {
// 	size_t i;

// 	i = 0;
// 	while (*str)
// 	{
// 		i++;
// 		str++;
// 	}
// 	return (i);
// }

// size_t	ft_strlen(const char *str)
// {
// 	int len = 0;
// 	while (42)
// 	{
// 		unsigned long x = *(unsigned long*)str;

// 		if((x & 0xFF) == 0)
// 			return len;
// 		if((x & 0xFF00) == 0)
// 			return len + 1;
// 		if((x & 0xFF0000) == 0)
// 			return len + 2;
// 		if((x & 0xFF000000) == 0)
// 			return len + 3;
// 		str += 4, len += 4;
// 	}
// 	return (len);
// }

/*
size_t ft_strlen (const char *str)
{
	const char				*char_ptr;
	const unsigned long int	*longword_ptr;
	unsigned long int		longword, magic_bits, himagic, lomagic;

	char_ptr = str;
	while (((unsigned long int) char_ptr & (sizeof (longword) - 1)))
	{
		if (*char_ptr == '\0')
			return char_ptr - str;
		char_ptr++;
	}
	longword_ptr = (unsigned long int *) char_ptr;
	if (sizeof (longword) > 4)
	{
		magic_bits = ((0x7efefefeL << 16) << 16) | 0xfefefeffL;
		himagic = ((0x80808080L << 16) << 16) | 0x80808080L;
		lomagic = ((0x01010101L << 16) << 16) | 0x01010101L;
	}
	const char *cp;
while (42)
	{
		longword = *longword_ptr++;
		if ((longword - lomagic) & himagic)
		{
			cp = (const char *) (longword_ptr - 1);
			if (cp[0] == 0)
				return cp - str;
			if (cp[1] == 0)
				return cp - str + 1;
			if (cp[2] == 0)
				return cp - str + 2;
			if (cp[3] == 0)
				return cp - str + 3;
			if (cp[4] == 0)
				return cp - str + 4;
			if (cp[5] == 0)
				return cp - str + 5;
			if (cp[6] == 0)
				return cp - str + 6;
			if (cp[7] == 0)
				return cp - str + 7;
		}
		}
}
*/
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

size_t ft_strlen(const char *str)
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
