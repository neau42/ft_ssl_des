/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:27:56 by no                #+#    #+#             */
/*   Updated: 2018/11/19 23:04:40 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		short_usage(char *str)
{
	ft_printf("usage:\n%s <md5|sha-256> [-hpqrs] \n", str);
}

void		long_usage(char *str)
{
	short_usage(str);
}
