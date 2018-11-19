/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_first.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 20:35:59 by no                #+#    #+#             */
/*   Updated: 2018/09/17 07:13:06 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsplit_first(char *str, char c)
{
	void *ptr;

	ptr = str;
	while (*str)
	{
		if (*str == c)
		{
			while ((str + 1) && *(str + 1) == c)
			{
				*str = '\0';
				str++;
			}
			*str = '\0';
			return (str + 1);
		}
		str++;
	}
	return (ptr);
}
