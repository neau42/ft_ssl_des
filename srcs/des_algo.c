/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 04:00:08 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/13 07:46:04 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint8_t g_pc1[] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10,
	2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23,
	15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28,
	20, 12, 4};

uint8_t g_pc2[] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12,
	4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45,
	33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

uint8_t g_ip[] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12,
	4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41,
	33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13,
	5, 63, 55, 47, 39, 31, 23, 15, 7};

uint32_t l_rot28(uint32_t n, unsigned int c)
{
	return (((n << c) | (n >> ((sizeof n * 7) - c))) & 0xFFFFFFF);
}

uint64_t	permut_bits(uint64_t original_len, uint64_t final_len,
								uint64_t value, uint8_t *tab)
{
	int			i;
	uint64_t	ret;

	i = -1;
	ret = 0;
	while (++i < (int)final_len)
		ret |= (((value & (1UL << (original_len - tab[i])))
				>> (original_len - tab[i])) << ((final_len - 1) - i));
	return (ret);
}

void	gen_keytab(uint64_t key, uint64_t *k)
{
	int			i;
	uint64_t	tmp;
	uint32_t	c0;
	uint32_t	d0;

	tmp = permut_bits(64, 56, key, g_pc1);
	c0 = 0xFFFFFFF & (tmp >> 28);
	d0 = 0xFFFFFFF & tmp;
	i = 0;
	while (++i < 17)
	{
		c0 = l_rot28(c0, (i < 3 || i == 9 || i == 16) ? 1 : 2);
		d0 = l_rot28(d0, (i < 3 || i == 9 || i == 16) ? 1 : 2);
		k[i - 1] = permut_bits(56, 48, d0 + ((uint64_t)c0 << 28), g_pc2);
	}
	i = 0;
	while (i++ < 16)
		ft_printf("k  [% .2d]: %48.48lb\n\n", i, k[i - 1]);

}
void		des_algo(const uint32_t *ptr, t_chksum *sum)
{
	char		buffer[64];
	uint64_t	k[16];
	t_des		*des;

	

	(void)sum;
	des = (t_des *)ptr;
	ft_printf("des algo\nKEY: %016.16llX\nVECTOR: %016.16llX\nSALT: %016.16llX\npass: %s\n",
		(des->key_val), (des->vec_val), (des->salt_val), des->pass);
	gen_keytab(des->key_val, k);
	ft_bzero(buffer, 64);

	uint64_t test = 0x0123456789ABCDEF;
	ft_printf("test : %0.64llb\n", test);
	
	test = permut_bits(64, 64, test, g_ip);
	ft_printf("test : %0.64llb\n", test);


	uint32_t left[17], right[17];
	right[0] = test;
	left[0] = (test >> 32);

	ft_printf("left : %0.32llb\nright: %0.32llb\n", left[0], right[0]);


	// while ((buf_size = read(des->fd_i, buf, 64)) > 0)
	// {
	

	// 	ft_bzero(buf, 64);
	// }
	

	// step_one(des);
}
