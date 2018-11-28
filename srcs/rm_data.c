/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/28 02:34:42 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	free_des(t_des *base)
{

	if (base->pass)
		free(base->pass);
	if (base->key)
		free(base->key);
	if (base->salt)
		free(base->salt);
	if (base->vector)
		free(base->vector);
	// ft_printf("free_des\n");
}

static void	free_base(t_base64 *b)
{
	if (b->input)
		free(b->input);
	if (b->output)
		free(b->output);
	if (b->type >= DES_TYPE)
		free_des((t_des *)b);
	// ft_printf("free_base\n");
	free(b);
}

void		rm_arg(t_arg *arg)
{
	if (arg)
	{
		// ft_printf("free_arg START\n");

		if (arg->type >= BASE64_TYPE)
		{
			free_base((t_base64 *)arg->base);
			arg->base = NULL;
		}
		ft_strdel(&arg->str);
		rm_arg(arg->next);
		// ft_printf("free_arg END\n");
		free(arg);
		arg = NULL;
	}
}
