/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_des.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/17 15:10:48 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char		*sum_to_str(t_chksum *sum, char *pass)
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

char		*concat_pass_salt(char *pass, uint64_t salt)
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

uint64_t	generate_key(uint32_t hashtype, char *pass, uint64_t salt, int type)
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

uint64_t	str_to_uint64(unsigned char *str)
{
	return ((uint64_t)str[7] | (uint64_t)str[6] << 8
	| (uint64_t)str[5] << 16 | (uint64_t)str[4] << 24
	| (uint64_t)str[3] << 32 | (uint64_t)str[2] << 40
	| (uint64_t)str[1] << 48 | (uint64_t)str[0] << 56);
}

int			get_magic_salt(int fd, uint64_t *salt_val, uint32_t opts,
											uint64_t *buf_save)
{
	char			buf[65];
	unsigned char	*ptr;

	ft_bzero(buf, 65);
	if ((opts & OPT_A
	&& (read_trim(fd, buf, 64) < 32))
	|| (!(opts & OPT_A) && (read(fd, buf, 16) < 16)
	&& ft_fdprintf(2, "error reading input file\n")))
		return (0);
	if (opts & OPT_A)
	{
		b64_decode_str((char *)buf, (char *)buf_save, 65);
		ptr = (unsigned char *)buf_save;
	}
	else
		ptr = (unsigned char *)buf;
	if (ft_strncmp("Salted__", (char *)ptr, 8))
	{
		ft_fdprintf(2, "bad magic number\n");
		return (0);
	}
	*salt_val = str_to_uint64(&ptr[8]);
	return (1);
}

int			gen_key_vec_salt(t_des *des, uint32_t opts, uint64_t *buf)
{
	if (opts & OPT_D && !des->key)
	{
		if (!get_magic_salt(des->fd_i, &des->salt_val, opts, buf))
			return (0);
	}
	else
		des->salt_val = (!des->salt) ? (rand() + ((uint64_t)rand() << 32))
			: ft_atoh_rpadd(des->salt);
	des->key_val = (!des->key) ?
		generate_key(OPT_MD5, des->pass, des->salt_val, 0)
		: ft_atoh_rpadd(des->key);
	if ((opts & GET_HASH) == OPT_CBC)
		des->vec_val = (!des->vector) ?
		generate_key(OPT_MD5, des->pass, des->salt_val, 1)
		: ft_atoh_rpadd(des->vector);
	return (1);
}

t_chksum	process_des(t_arg *arg, uint32_t opts, uint8_t print)
{
	t_des		*des;
	uint64_t	buf[8];

	(void)print;
	ft_bzero(buf, sizeof(uint64_t) * 8);
	des = (t_des *)arg->base;
	if ((des->fd_i = get_input_file(des->input)) < 0
	|| (des->fd_o = get_output_file(des->output)) < 0
	|| !valid_params(des, opts))
	{
		des_close_n_free(des);
		return ((t_chksum)0);
	}
	if (gen_key_vec_salt(des, opts, buf))
		(opts & OPT_D) ? des_algo_decrypt(des, opts, &buf[2])
		: algo(des, NULL, opts);
	des_close_n_free(des);
	return ((t_chksum)1);
}
