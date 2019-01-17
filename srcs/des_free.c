/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/17 18:02:01 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		des_free(t_des *des)
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

void			des_close_n_free(t_des *des)
{
	if (des->fd_i != STDIN_FILENO)
		close(des->fd_i);
	if (des->fd_o > STDOUT_FILENO)
		close(des->fd_o);
	des_free(des);
}
