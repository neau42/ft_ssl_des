/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 23:07:03 by nboulaye          #+#    #+#             */
/*   Updated: 2016/10/31 01:16:07 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(const char *s1, const char *s2)
{
	char	*ret;

	if (!s1 || !s2 || !(ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ret = ft_strcpy(ret, s1);
	ret = ft_strcat(ret, s2);
	return (ret);
}
