/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/27 04:16:38 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void free_des(t_des *base)
{
	if (base->pass)
		free(base->pass);
	if (base->key)
		free(base->key);
	if (base->salt)
		free(base->salt);
	if (base->vector)
		free(base->vector);
}

void	rm_arg(t_arg *arg)
{
	if (arg)
	{
		if (arg->type >= BASE64_TYPE)
		{
			if (arg->base->input)
				free(arg->base->input);
			if (arg->base->output)
				free(arg->base->output);
			if (arg->type >= DES_TYPE)
				free_des((t_des *)arg->base);
			free(arg->base);
			arg->base = NULL;
		}
		ft_strdel(&arg->str);
		rm_arg(arg->next);
		free(arg);
		arg = NULL;
	}
}
