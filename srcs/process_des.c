/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_des.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/12 20:57:28 by nboulaye         ###   ########.fr       */
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
		// ft_printf("tmp[%d] :: '%s', len: %d\n", i, tmp[i], len);
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

uint64_t		ft_pbkdf_maison(uint32_t hashtype, char *pass, uint64_t salt, int iter)
{
	char		salt_buf[64];
	char		iter_buf[16];
	t_arg		arg;
	t_chksum	sum;
	uint64_t	result;
	int i;

	arg.type = STRING_TYPE;
	arg.base = NULL;
	arg.next = NULL;
	ft_itoa_base_buffer_upper(salt, 16, salt_buf);
	ft_itoa_base_buffer(iter, 10, iter_buf);
	i = ft_strlen(salt_buf) + ft_strlen(iter_buf);
	ft_printf("test concat iter withSalt, len: %d , (iter & 0xFF): %d ", i, (iter & 0xFF));
	ft_strcat(salt_buf, iter_buf);
	ft_printf("test concat iter withSalt, len: %d , (iter & 0xFF): %d ", i, (iter & 0xFF));
	if (!(arg.str = ft_strjoin(pass, salt_buf)))
	{
		ft_fdprintf(2, "malloc error\n");
		exit (42);
	}
	sum = process_string(&arg, hashtype, 0);
	// ft_printf("|%08x%08x%08x%08x%08x%08x%08x%08x|\n", sum.sha256[0], sum.sha256[1],
	// sum.sha256[2], sum.sha256[3], sum.sha256[4], sum.sha256[5], sum.sha256[6], sum.sha256[7]);
	free(arg.str);
	while (--iter > 0)
	{
		arg.str = sum_to_str(&sum, pass);
		// ft_printf("tmpStr:: '%s'\n", arg.str);
		sum = process_string(&arg, hashtype, 0);
		// ft_printf("chksum: TMP[%d]: ", iter);
		ft_printf("|%08x%08x%08x%08x%08x%08x%08x%08x|\n", sum.sha256[0], sum.sha256[1],
			sum.sha256[2], sum.sha256[3], sum.sha256[4], sum.sha256[5], sum.sha256[6], sum.sha256[7]);
		free(arg.str);
	}
	ft_printf("|%08x%08x%08x%08x%08x%08x%08x%08x|\n", sum.sha256[0], sum.sha256[1],
		sum.sha256[2], sum.sha256[3], sum.sha256[4], sum.sha256[5], sum.sha256[6], sum.sha256[7]);

	result = sum.sha256[1] + ((uint64_t)sum.sha256[0] << 32);
	return (result);
}

void		gen_key_vec_salt(t_des *des)
{
	des->salt_val = (!des->salt) ? (rand() + ((uint64_t)rand() << 32))
			: ft_atoh_rpadd(des->salt);
	des->key_val = (!des->key) ? ft_pbkdf_maison(OPT_SHA256, des->pass, des->salt_val, 1000)
			: ft_atoh_rpadd(des->key);
	des->vec_val = ft_atoh_rpadd(des->vector);
}

t_chksum	process_des(t_arg *arg, uint32_t opts, uint8_t print)
{
	t_des		*des;

	(void)opts;
	(void)print;
	ft_printf("process_des\n");
	des = (t_des *)arg->base;
	if ((des->fd_i = get_input_file(des->input)) < 0
	|| (des->fd_o = get_output_file(des->output)) < 0
	|| !valid_params(des))
	{
		close_fds(des);
		return ((t_chksum)0);
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
	return ((t_chksum)1);
}