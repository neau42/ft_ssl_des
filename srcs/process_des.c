/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_des.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/09 15:58:29 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void free_des(t_des *des)
{
	if (des->pass)
		free(des->pass);
	if (des->vector)
		free(des->vector);
	if (des->salt)
		free(des->salt);
	if (des->key)
		free(des->key);
	des->pass = NULL;
	des->vector = NULL;
	des->salt = NULL;
	des->key = NULL;
}

static void close_n_free(t_des *des)
{
	if (des->fd_i != STDIN_FILENO)
		close(des->fd_i);
	if (des->fd_o > STDOUT_FILENO)
		close(des->fd_o);
	free_des(des);
}

static int	ft_getpass(t_des *des)
{
	char	*str;

	des->pass = ft_strdup(getpass("(enter des encryption password) $> "));
	str = getpass("(Verifying - enter des encryption password:)) $> ");
	if (!des->pass || !*des->pass || ft_strcmp(des->pass, str))
	{
		ft_printf("Verify failure\n");
		ft_fdprintf(2, "bad password read\n");
		close_n_free(des);
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

int		valid_hex_val(t_des *des)
{
	if (des->salt && !valid_hex_value(des->salt)) // if des-cbc
	{
		ft_fdprintf(2, "non-hex digit\ninvalid hex salt value");
		return (0);
	}
	if (des->key && !valid_hex_value(des->key))
	{
		ft_fdprintf(2, "non-hex digit\ninvalid hex key value");
		return (0);
	}
	if (des->vector && !valid_hex_value(des->vector)) // if des-cbc
	{
		ft_fdprintf(2, "non-hex digit\ninvalid hex vector value");
		return (0);
	}
	return (1);
}

int valid_params(t_des *des, uint32_t opts)
{
	if (!des->pass && !des->key)
	{
		if (!ft_getpass(des))
			return (0);
	}
	else if (des->key)
	{
		if ((opts & GET_HASH) == OPT_CBC
		&& !des->vector)
			{
				ft_fdprintf(2, "vector undefined\n");
					return (0);
			}
			return (valid_hex_val(des));
	}
	return (valid_hex_val(des));
}

char			*sum_to_str(t_chksum *sum, char *pass)
{
	char		tmp[8][16];
	char		*ret;
	int			i;
	int			len;

	len = 0;
	i = 0;
	while (i < 8)
	{
		ft_itoa_base_buffer_upper(sum->sha256[i], 16, tmp[i]);
		len += ft_strlen(tmp[i]);
		i++;
	}
	len += ft_strlen(pass);
	if (!(ret = ft_strnew(len)))
		return (NULL);
	ft_strcpy(ret, pass);
	i = 0;
	while (i < 8)
		ft_strcat(ret, tmp[i++]);
	return (ret);
}

char			*concat_pass_salt(char *pass, uint64_t salt)
{
	int			len;
	char		*str;

	len = (pass) ? ft_strlen(pass) : 0;
	if (!(str = ft_strnew(len + 8)))
	{
		ft_fdprintf(2, "malloc error\n");
		exit(42);
	}
	if (pass)
	ft_strcpy(str, pass);
	str[len + 7] = (salt & 0xFF);
	str[len + 6] = ((salt >> 8) & 0xFF);
	str[len + 5] = ((salt >> 16) & 0xFF);
	str[len + 4] = ((salt >> 24) & 0xFF);
	str[len + 3] = ((salt >> 32) & 0xFF);
	str[len + 2] = ((salt >> 40) & 0xFF);
	str[len + 1] = ((salt >> 48) & 0xFF);
	str[len] = ((salt >> 56) & 0xFF);
	return (str);
}

uint64_t		generate_key(uint32_t hashtype, char *pass, uint64_t salt, int type)
{
	t_arg		arg;
	t_chksum	sum;

	arg.type = STRING_TYPE;
	arg.base = NULL;
	arg.next = NULL;
	arg.str = concat_pass_salt(pass, salt);
	sum = process_string_custom(&arg, hashtype, ft_strlen(pass) + 8);
	free(arg.str);
	return (type == 0) ?
	(endian_swap32(sum.md5[1]) + ((uint64_t)endian_swap32(sum.md5[0]) << 32)) :
	(endian_swap32(sum.md5[3]) + ((uint64_t)endian_swap32(sum.md5[2]) << 32));
}

void		gen_key_vec_salt(t_des *des, uint32_t opts)
{
	des->salt_val = (!des->salt) ? (rand() + ((uint64_t)rand() << 32))
			: ft_atoh_rpadd(des->salt);
	des->key_val = (!des->key) ? generate_key(OPT_MD5, des->pass, des->salt_val, 0)
			: ft_atoh_rpadd(des->key);
	if ((opts & GET_HASH) == OPT_CBC)
		des->vec_val = (!des->vector) ? generate_key(OPT_MD5, des->pass, des->salt_val, 1)
		: ft_atoh_rpadd(des->vector);
}

t_chksum process_des_ecb(t_arg *arg, uint32_t opts, uint8_t print)
{
	t_des		*des;

	(void)print;
	des = (t_des *)arg->base;
	if ((des->fd_i = get_input_file(des->input)) < 0
	|| (des->fd_o = get_output_file(des->output)) < 0
	|| !valid_params(des, opts))
	{
		close_n_free(des);
		return ((t_chksum)0);
	}
	gen_key_vec_salt(des, opts);
	algo(des, NULL, opts);
	close_n_free(des);
	return ((t_chksum)1);
}