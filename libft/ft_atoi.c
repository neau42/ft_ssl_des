/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 22:32:21 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/20 13:25:30 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int64_t		ft_atoi(const char *str)
{
	uint64_t		absnbr;
	uint64_t		tmp;
	char			invers;

	absnbr = 0;
	invers = 0;
	while (*str == ' ' || (*str <= 13 && *str >= 9))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			invers = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tmp = absnbr;
		absnbr *= 10;
		if (absnbr < tmp)
			return (invers - 1);
		absnbr += *str - 48;
		str++;
	}
	return (invers == 0) ? (absnbr) : (-absnbr);
}
