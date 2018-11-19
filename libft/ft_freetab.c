/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 18:50:32 by no                #+#    #+#             */
/*   Updated: 2018/11/18 17:15:39 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_tabstrdel(char **t)
{
	if (*t)
		ft_tabstrdel(t + 1);
	free(*t);
	*t = NULL;
}

void			ft_freetab(char ***t)
{
	ft_tabstrdel(*t);
	free(*t);
	*t = NULL;
}
