/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_des_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:35:57 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/17 19:15:51 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int			ft_getpass(t_des *des, uint32_t opts)
{
	if (opts & OPT_D)
	{
		if (!(des->pass =
		ft_strdup(getpass("(enter des decryption password) $> ")))
		|| !*des->pass)
			return (0);
		return (1);
	}
	des->pass = ft_strdup(getpass("(enter des encryption password) $> "));
	if (!des->pass || !*des->pass || ft_strcmp(des->pass,
	getpass("(Verifying - enter des encryption password:)) $> ")))
	{
		ft_printf("Verify failure\n");
		ft_fdprintf(2, "bad password read\n");
		des_close_n_free(des);
		return (0);
	}
	ft_printf("pass: %s\n", des->pass);
	return (1);
}

static int			valid_hex_value(char *str)
{
	while (*str)
	{
		if (!(ft_ishexdigit(*str)))
			return (0);
		str++;
	}
	return (1);
}

static int			valid_hex_val(t_des *des)
{
	if (des->salt && !valid_hex_value(des->salt))
	{
		ft_fdprintf(2, "non-hex digit\ninvalid hex salt value");
		return (0);
	}
	if (des->key && !valid_hex_value(des->key))
	{
		ft_fdprintf(2, "non-hex digit\ninvalid hex key value");
		return (0);
	}
	if (des->vector && !valid_hex_value(des->vector))
	{
		ft_fdprintf(2, "non-hex digit\ninvalid hex vector value");
		return (0);
	}
	return (1);
}

int					valid_params(t_des *des, uint32_t opts)
{
	if (!des->pass && !des->key)
	{
		if (!ft_getpass(des, opts))
			return (0);
	}
	else if (des->key)
	{
		if ((opts & GET_HASH) >= OPT_CBC
		&& !des->vector)
		{
			ft_fdprintf(2, "vector undefined\n");
			return (0);
		}
		return (valid_hex_val(des));
	}
	return (valid_hex_val(des));
}
