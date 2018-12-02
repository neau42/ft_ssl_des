/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_des.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/02 10:26:59 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void close_fds(t_des *des)
{
	if (des->fd_i != STDIN_FILENO)
		close(des->fd_i);
	if (des->fd_o > STDOUT_FILENO)
		close(des->fd_o);
}

static int	ft_getpass(t_des *des)
{
	char	*str;

	des->pass = ft_strdup(getpass("(enter des encryption password) $> "));
	str = getpass("(Verifying - enter des encryption password:)) $> ");
	if (!des->pass || ft_strcmp(des->pass, str))
	{
		ft_printf("Verify failure\n");
		ft_fdprintf(2, "bad password read\n");
		close_fds(des);
		return (0);
	}
	ft_printf("pass: %s\n", des->pass);
	return (1);
}

int			valid_hex_value(char *str)
{
	while (*str)
	{
		if (!(ft_ishexdigit(*str)))
			return (0);
		str++;
	}
	return (1);
}

int		valid_key_n_vector(t_des *des)
{
	if (!des->vector)
	{
		ft_fdprintf(2, "vector undefined\n");
		return (0);
	}
	if (!valid_hex_value(des->key))
	{
		ft_fdprintf(2, "non-hex digit\ninvalid hex key value");
		return (0);
	}
	if (!valid_hex_value(des->vector))
	{
		ft_fdprintf(2, "non-hex digit\ninvalid hex vector value");
		return (0);
	}
	return (1);
}

int		process_des(t_arg *arg, uint32_t opts)
{
	t_des	*des;

	(void)opts;
	ft_printf("process_des\n");
	des = (t_des *)arg->base;
	if ((des->fd_i = get_input_file(des->input)) < 0
	|| (des->fd_o = get_output_file(des->output)) < 0)
	{
		close_fds(des);
		return (1);
	}
	if (!des->pass && !des->key)
	{
		if (!ft_getpass(des))
		{
			close_fds(des);
			return (1);
		}
	}
	else if (des->key)
	{
		if (!(valid_key_n_vector(des)))
		{
			close_fds(des);
			return (1);
		}
	}


	ft_printf("process_des ...........\n");
	ft_printf("KEY: %llx\nVECTOR: %llx\nSALT: %llx\npass: %s\n", ft_atoh_rpadd(des->key), ft_atoh_rpadd(des->vector), ft_atoh_rpadd(des->salt), des->pass);

	close_fds(des);
	return (0);
}