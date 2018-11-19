/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 18:59:47 by amerelo           #+#    #+#             */
/*   Updated: 2018/11/18 17:15:55 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_free(char *s1, char *s2, int i)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
		return (NULL);
	if (i & 1)
	{
		free(s1);
		s1 = NULL;
	}
	if (i & 2)
	{
		free(s2);
		s2 = NULL;
	}
	return (join);
}
