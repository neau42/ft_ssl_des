/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_base64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/14 06:23:20 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	close_fds(t_base64 *base)
{
	if (base->fd_i != STDIN_FILENO)
		close(base->fd_i);
	if (base->fd_o > STDOUT_FILENO)
		close(base->fd_o);
}

t_chksum	process_base64(t_arg *arg, uint32_t opts, uint8_t print)
{
	t_base64	*base;
	(void)print;
	base = (t_base64 *)arg->base;
	if ((base->fd_i = get_input_file(base->input)) < 0
	|| (base->fd_o = get_output_file(base->output)) < 0)
	{
		close_fds(base);
		return ((t_chksum)0);
	}
	((opts & OPT_D)) ? b64_decode(base) : b64_encode(base);
	close_fds(base);
	return ((t_chksum)1);
}
