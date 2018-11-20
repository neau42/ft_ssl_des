/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/20 04:42:31 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void rm_arg(t_arg *arg)
{
	if (arg)
	{
		ft_printf("remove '%s'\n", arg->str);
		ft_strdel(&arg->str);
		rm_arg(arg->next);
		free(arg);
		arg = NULL;
	}
}
