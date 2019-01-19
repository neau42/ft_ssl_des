/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 04:00:08 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/19 03:46:39 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		des_print(t_des *des, uint64_t *final_buf, int *i, uint32_t opts)
{
	if (*i == 6)
	{
		(opts & OPT_A) ?
		b64_encode_buffer((t_base64 *)des, (char *)final_buf, 48)
		: write(des->fd_o, final_buf, 48);
		*i = 0;
	}
}

uint64_t	add_padding(int read_size, uint64_t *buf)
{
	uint64_t padding;
	uint64_t padding_nb;

	padding = (int)(sizeof(uint64_t)) - read_size;
	padding_nb = (int)(sizeof(uint64_t)) - read_size;
	while (padding_nb-- > 0)
		*buf |= (padding << (uint64_t)(64 - (padding_nb + 1) * 8));
	return (padding);
}

void		read_loop(t_des *des, uint64_t *k, uint64_t *final_buf,
														uint32_t opts)
{
	int			i;
	int			read_size;
	uint64_t	padding;

	i = (des->pass) ? 2 : 0;
	des->buf = 0;
	padding = 100;
	while ((read_size = read(des->fd_i, &des->buf, (sizeof(uint64_t)))) > 0)
	{
		padding = (read_size < (int)(sizeof(uint64_t))) ?
		add_padding(read_size, &des->buf) : 100;
		process_des_chunk(des, k, &final_buf[i], opts);
		i++;
		des_print(des, final_buf, &i, opts);
		des->buf = 0;
	}
	if (padding == 100 && (des->buf = 0x0808080808080808))
		process_des_chunk(des, k, &final_buf[i++], opts);
	if (i)
	{
		(opts & OPT_A) ?
		b64_encode_buffer((t_base64 *)des, (char *)final_buf, i * 8) :
		write(des->fd_o, final_buf, i * 8);
	}
}

void		des_algo(const uint32_t *ptr, t_chksum *sum, uint32_t opts)
{
	uint64_t	*k;
	t_des		*des;
	uint64_t	final_buf[6];
	uint64_t	test;

	(void)sum;
	ft_bzero(final_buf, sizeof(uint64_t) * 6);
	des = (t_des *)ptr;
	if (des->pass)
	{
		ft_memcpy((uint8_t *)&final_buf[0], "Salted__", 8);
		test = endian_swap64((uint64_t)des->salt_val);
		ft_memcpy((uint8_t *)&final_buf[1], &test, 8);
	}
	k = des_gen_keytab(des->key_val);
	if (opts & OPT_PP)
		ft_fdprintf(2, "Key : %016.16llX\nVect: %016.16llX\nSalt:"
	"%016.16llX\nPass: %s\n", (des->key_val), (des->vec_val),
	(des->salt_val), des->pass);
	read_loop(des, k, final_buf, opts);
}
