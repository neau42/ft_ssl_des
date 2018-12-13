/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 04:00:08 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/13 05:42:30 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// void	step_one(t_des *des)
// {
	uint8_t g_pc1[] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10,
	2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23,
	15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28,
	20, 12, 4};

// }

// void modif()
// {
// 	for (int i = 0; i < 56; i++)
// 	{
// 		g_pc1[i] = 64 - (g_pc1[i]);
// 	}
// }

uint64_t	permut_key(uint64_t key)
{
	uint8_t		i;
	uint64_t	new_key;

	new_key = 0;
	i = 0;
	while (i < 56)
	{
		new_key |= (((key & (1UL << (64 - g_pc1[i]))) >> (64 - g_pc1[i])) << (55UL - i));
		i++;
	}
	ft_printf("\n-> %.64llb\n", new_key);
	return (new_key);
}


void		des_algo(const uint32_t *ptr, t_chksum *sum)
{
	char	buffer[64];
	t_des	*des;
	// int		buf_size;

	(void)sum;
	des = (t_des *)ptr;
	ft_printf("des algo\nKEY: %016.16llX\nVECTOR: %016.16llX\nSALT: %016.16llX\npass: %s\n",
		(des->key_val), (des->vec_val), (des->salt_val), des->pass);
	
	permut_key(des->key_val);
	ft_bzero(buffer, 64);

	// while ((buf_size = read(des->fd_i, buf, 64)) > 0)
	// {
	

	// 	ft_bzero(buf, 64);
	// }
	

	// step_one(des);
}
