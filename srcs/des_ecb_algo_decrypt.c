/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_algo_decrypt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:35:57 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/13 00:41:49 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	ft_des_rounds_rev(uint64_t msg, uint64_t *k)
{
	uint32_t	left;
	uint32_t	right;
	uint32_t	tmp_right;
	int			i;

	left = msg;
	right = (msg >> 32);
	i = 16;
	while (--i >= 0)
	{
		tmp_right = right;
		right = left;
		left = tmp_right ^ ft_f(left, k[i]);
	}
	return (right + ((uint64_t)left << 32));
}

static int	last_chunk_rm_padd(uint64_t msg, uint64_t *k, t_des *des)
{
	uint64_t	result;
	uint8_t		pad;
	int		pad_save;

	result = endian_swap64(unpermut_bits(64, ft_des_rounds_rev(unpermut_bits(64, endian_swap64(msg), g_ip_rev), k), g_ip));
	pad = result >> 56;
	pad_save = pad;

	while (pad_save > 0)
	{
		if ((result >> (64 - (pad_save * 8)) & 0xff) != pad)
		{
			write(des->fd_o, &result, 8 - pad);
			return (0);
		}
		pad_save--;
	}
	write(des->fd_o, &result, 8 - pad);
	return (1);
}

// int get_magic_salt(int fd, uint64_t *salt_val, uint32_t opts)
// {
// 	unsigned char buf[17];

// 	ft_bzero(buf, 17);
// 	if (opts & OPT_A)
// 	{
// 		ft_printf("NEED decode b64!\n");
// 	}
// 	int tst;
// 	if ((tst = read(fd, buf, 16)) < 16)
// 	{
// 		ft_fdprintf(2, "error reading input file: size: %d\n", tst);
// 		// return (0);
// 	}
// 	ft_printf("BUF FOR SALT:'%s'\n", buf);
// 	if (ft_strncmp("Salted__", (char *)buf, 8))
// 	{
// 		ft_fdprintf(2, "bad magic number: %s\n", buf);
// 		return (0);
// 	}
// 	*salt_val = ((uint64_t)buf[15] | (uint64_t)buf[14] << 8 | (uint64_t)buf[13] << 16 | (uint64_t)buf[12] << 24 | (uint64_t)buf[11] << 32 | (uint64_t)buf[10] << 40 | (uint64_t)buf[9] << 48 | (uint64_t)buf[8] << 56);
// 	ft_fdprintf(2, "[TST] magic salt: %016llx\n", (*salt_val));
// 	return (1);
// }

void	des_ecb_algo_decrypt(t_des *des, uint32_t opts, uint64_t *buf)
{
	uint64_t	k[16];
	uint64_t	result;
	// uint64_t	buf;
	uint64_t	msg;

	msg = buf[0];

	ft_fdprintf(2, "[BUF]: %016llx\n", buf[0]);
	ft_fdprintf(2, "[BUF]: %016llx\n", buf[1]);
	ft_fdprintf(2, "[BUF]: %016llx\n", buf[2]);
	ft_fdprintf(2, "[BUF]: %016llx\n", buf[3]);
	ft_fdprintf(2, "[BUF]: %016llx\n", buf[4]);
	// ft_fdprintf(2, "[BUF]: %016llx\n", buf[5]);
	des_gen_keytab(des->key_val, k);
	// if (!get_magic_salt(des->fd_i, &des->salt_val, opts))
	// {
	// 	// ft_printf()
	// 	return ;
	// }
	while (read(des->fd_i, &buf[0], (sizeof(uint64_t))) > 0)
	{
		if (msg)
		{
			result = endian_swap64(unpermut_bits(64, ft_des_rounds_rev(
			unpermut_bits(64, endian_swap64(msg), g_ip_rev), k), g_ip));
			write(des->fd_o, &result, 8);
		}
		msg = buf[0];
	}
	if (!last_chunk_rm_padd(msg, k, des))
		ft_printf("bad decrypt\n");
	if (opts & OPT_PP)
		ft_fdprintf(2, "Key : %016.16llX\nVect: %016.16llX\nSalt: %016.16llX\nPass: %s\n",
					(des->key_val), (des->vec_val), (des->salt_val), des->pass);
}
