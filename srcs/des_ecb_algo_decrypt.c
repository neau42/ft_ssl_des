/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_algo_decrypt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:35:57 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/15 17:22:23 by no               ###   ########.fr       */
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

int	last_chunk_rm_padd(uint64_t msg, uint64_t *k, t_des *des)
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

void decode_msg(t_des *des, uint64_t *msg, uint64_t *k, int size)
{
	uint64_t result;

	while (size--)
	{
		result = endian_swap64(unpermut_bits(64, ft_des_rounds_rev(unpermut_bits(64, endian_swap64(*msg), g_ip_rev), k), g_ip));
		ft_fdprintf(2, "*msg[%d]:(%016llx) '", size, *msg);
		write(2, msg, 8);
		ft_fdprintf(2, "', result:\n", *msg);
		write(des->fd_o, &result, 8);
		ft_fdprintf(2, "\n");
		msg++;
	}
}

// uint64_t	ft_tst(unsigned char *str)
// {
// 	uint64_t ret;

// 	ret = str[0] + (str[1] << 8) + (str[2] << 16) + (str[3] << 24) + ((uint64_t)str[4] << 32) + ((uint64_t)str[5] << 40) + ((uint64_t)str[6] << 48) + ((uint64_t)str[7] << 56);
// 	return (ret);
// }

//./ft_ssl des-ecb -a -i f_100  -p coucou -s 123 | ./ft_ssl des-ecb -a -p coucou -s 123 -d

void 	init_bufs(void *msg, void *b64_buf, void *final_buf)
{
	ft_bzero(msg, 48);
	ft_bzero(b64_buf, 65);
	ft_bzero(final_buf, 49);
}

void	des_ecb_algo_decrypt(t_des *des, uint32_t opts, uint64_t *buf)
{
	uint64_t	k[16];
	uint64_t	msg[6];
	char 		b64_buf[65];
	char 		final_buf[49];
	int			read_size;

	des_gen_keytab(des->key_val, k);
	init_bufs(msg, b64_buf, final_buf);
	while (buf[0])
		decode_msg(des, buf++, k, 1);
	while ((!(opts & OPT_A) && (read_size = read(des->fd_i, &msg, 48)) > 0)
	|| ((opts & OPT_A) && (read_size = read_without_space(des->fd_i, b64_buf, 64)) > 0))
	{
		if (opts & OPT_A)
		{
			b64_decode_str(b64_buf, final_buf, read_size);
			read_size = (read_size / 8 * 6 / 8) + ((read_size % 8) ? 1 : 0);
			ft_memcpy(msg, final_buf, read_size * 8);
			decode_msg(des, msg, k, read_size);
		}
		else
			decode_msg(des, msg, k, (read_size / 8) + ((read_size % 8) ? 1 : 0));
		init_bufs(msg, b64_buf, final_buf);
	}
}

// void	des_ecb_algo_decrypt(t_des *des, uint32_t opts, uint64_t *buf)
// {
// 	uint64_t	k[16];
// 	uint64_t	result;
// 	uint64_t	msg;
// 	char 		tst_buf[65];
// 	char 		tst_buf2[49];
// 	int			tst;

// 	msg = buf[0];
// 	ft_bzero(tst_buf, 64);
// 	ft_bzero(tst_buf2, 49);
// 	ft_fdprintf(2, "[BUF]: %016llx\n", buf[0]);
// 	ft_fdprintf(2, "[BUF]: %016llx\n", buf[1]);
// 	ft_fdprintf(2, "[BUF]: %016llx\n", buf[2]);
// 	ft_fdprintf(2, "[BUF]: %016llx\n", buf[3]);
// 	des_gen_keytab(des->key_val, k);
// 	while (buf[1])
// 	{
// 		ft_fdprintf(2, "[WHILE *BUF]: buf %016llx\n", buf[0]);
// 		if (msg)
// 		{
// 			ft_fdprintf(2, "[WHILE *BUF]: msg %016llx\n", msg);
// 			result = endian_swap64(unpermut_bits(64, ft_des_rounds_rev(unpermut_bits(64, endian_swap64(msg), g_ip_rev), k), g_ip));
// 			write(des->fd_o, &result, 8);
// 			ft_fdprintf(2, "\n");
// 		}
// 		buf++;
// 		msg = buf[0];
// 	}
// 	while ((!(opts & OPT_A) && (tst = 1) && read(des->fd_i, &buf[0], (sizeof(uint64_t))) > 0)
// 	|| ((opts & OPT_A) && (tst = read_without_space(des->fd_i, tst_buf, 64)) > 0))
// 	{
// 		if (opts & OPT_A)
// 		{
// 			tst = tst / 32 * 3;
// 			b64_decode_str(tst_buf, tst_buf2, 64);
// 			ft_fdprintf(2, "[READ   b64]: buf '%s', tst: %d\n", tst_buf, tst);
// 			ft_fdprintf(2, "[READ   b64]: buf2 '");
// 			write(2, tst_buf2, 49);
// 			ft_bzero(tst_buf, 65);
// 		}
// 		else
// 			ft_fdprintf(2, "[READnormal]: buf %016llx\n", buf[0]);
// 		while (tst > 0)
// 		{
// 			ft_fdprintf(2, "\ntst : %d\n", tst);
// 			if (msg)
// 				decode_msg(des, msg, k);
// 			if (opts & OPT_A)
// 			{
// 				// tst /= 6;
// 				msg = ft_tst((unsigned char*) &tst_buf2[48 - tst * 8]);
// 				msg = endian_swap64(msg);
// 				ft_fdprintf(2, "[<MSG>]: %016llx\n", msg);
// 				// b64_decode_str(&tst_buf[64 - tst * 8], (char *)&msg, 8);
// 				// ft_bzero(tst_buf, 64);
// 			}
// 			else
// 				msg = buf[0];
// 			tst--;
// 		}
// 		ft_bzero(tst_buf2, 49);
// 	}
// 	if (!last_chunk_rm_padd(msg, k, des))
// 		ft_printf("bad decrypt\n");
// 	if (opts & OPT_PP)
// 		ft_fdprintf(2, "Key : %016.16llX\nVect: %016.16llX\nSalt: %016.16llX\nPass: %s\n",
// 					(des->key_val), (des->vec_val), (des->salt_val), des->pass);
// }
