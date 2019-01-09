/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 22:32:21 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/09 22:29:05 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int64_t		ft_atoh(char *str)
{
	static char			tab[] = "0123456789ABCDEF";
	char				new_str[24];
	char				*tmp;
	char				*ptr;
	uint64_t			value;

	while (*str == ' ' || (*str <= 13 && *str >= 9))
		str++;
	value = 0;
	while (*str && value < 16)
	{
		new_str[value] = ft_toupper(*str);
		str++;
		value++;
	}
	new_str[value] = 0;
	ptr = new_str;
	value = 0;
	while (ft_ishexdigit(*ptr) && ((value *= 16) || 1))
	{
		tmp = ft_strchr(tab, *ptr);
		value += (tmp - tab);
		ptr++;
	}
	return (value);
}

int64_t		ft_atoh_rpadd(char *str)
{
	static char			tab[] = "0123456789ABCDEF";
	char				new_str[24];
	char				*ptr;
	uint64_t			value;

	if (!(value = 0) && !str)
		return (0);
	while (*str == ' ' || (*str <= 13 && *str >= 9))
		str++;
	while (value < 16)
	{
		new_str[value] = (*str) ? ft_toupper(*str) : '0';
		if (*str)
			str++;
		value++;
	}
	new_str[value] = 0;
	ptr = new_str;
	value = 0;
	while (ft_ishexdigit(*ptr) && ((value *= 16) || 1))
	{
		value += (ft_strchr(tab, *ptr) - tab);
		ptr++;
	}
	return (value);
}
