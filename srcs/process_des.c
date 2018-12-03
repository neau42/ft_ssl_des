/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_des.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/03 16:59:30 by nboulaye         ###   ########.fr       */
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
	if (!valid_hex_value(des->vector))// if des-ecb
	{
		ft_fdprintf(2, "non-hex digit\ninvalid hex vector value");
		return (0);
	}
	return (1);
}

int valid_params(t_des *des)
{
	if (!des->pass && !des->key)
	{
		if (!ft_getpass(des))
			return (0);
	}
	else if (des->key)
	{
		if (!des->pass && !(valid_key_n_vector(des)))
			return (0);
	}
	return (1);
}

uint64_t		gen_key(char *pass, uint64_t salt)
{
	char		salt_buf[17];
	t_arg		arg;

	arg.type = STRING_TYPE;
	arg.base = NULL;
	arg.next = NULL;
	ft_itoa_base_buffer(salt, 16, salt_buf);
	if (!(arg.str = ft_strjoin(pass, salt_buf)))
	{
		ft_fdprintf(2, "malloc error\n");
		exit (42);
	}
	ft_printf("\tsalt X: %llX, salt S: '%s', pass: '%s', concat: '%s'\n", salt, salt_buf, pass, arg.str);
	// ft_pbkdf2();
	free(arg.str);
	return (0x0123456789012345);
}

void gen_key_vec_salt(t_des *des)
{
	
	des->salt_val = (!des->salt) ? (rand() + ((uint64_t)rand() << 32))
			: ft_atoh_rpadd(des->salt);
	des->key_val = (!des->key) ? gen_key(des->pass, des->salt_val)
			: ft_atoh_rpadd(des->key);
	des->vec_val = ft_atoh_rpadd(des->vector);
}

int		process_des(t_arg *arg, uint32_t opts)
{
	t_des		*des;

	(void)opts;
	ft_printf("process_des\n");
	des = (t_des *)arg->base;
	if ((des->fd_i = get_input_file(des->input)) < 0
	|| (des->fd_o = get_output_file(des->output)) < 0
	|| !valid_params(des))
	{
		close_fds(des);
		return (1);
	}
	// ft_printf("KEY: %llx\nVECTOR: %llx\nSALT: %llx\npass: %s\n",
	// 	(des->key) ? ft_atoh_rpadd(des->key) : -1,
	// 	(des->vector) ? ft_atoh_rpadd(des->vector) : -1,
	// 	(des->salt) ? ft_atoh_rpadd(des->salt) : -1,
	// 	des->pass);
	gen_key_vec_salt(des);
	ft_printf("process_des ...........\n");

	ft_printf("KEY: %016.16llX\nVECTOR: %016.16llX\nSALT: %016.16llX\npass: %s\n",
			  (des->key_val), (des->vec_val), (des->salt_val), des->pass);

	close_fds(des);
	return (0);
}