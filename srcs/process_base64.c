/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_base64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/01 04:45:43 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		get_input_file(char *file_name)
{
	int	fd;

	if (file_name)
	{
		fd = open(file_name, O_RDONLY);
		if (fd < 0)
			ft_fdprintf(2, "ft_ssl: %s: No such file or directory\n", file_name);
	}
	else
		fd = STDIN_FILENO;
	return (fd);
}

int		get_output_file(char *file_name)
{
	int fd;

	if (file_name)
	{
		fd = open(file_name, O_WRONLY | O_CREAT, 0644);
		if (fd < 0)
			ft_fdprintf(2, "ft_ssl: %s: No such file or directory\n", file_name);
	}
	else
		fd = STDOUT_FILENO;
	return (fd);
}

void	close_fds(t_base64 *base)
{
	if (base->fd_i != STDIN_FILENO)
		close(base->fd_i);
	if (base->fd_o > STDOUT_FILENO)
		close(base->fd_o);
}

void b64_decode(t_base64 *base, char *buf, int len, char *tab)//bufsize = 4
{
	char val[3];
	char	idx[4];
	int		size;
	char	*ptr;

	if (!(size = len % 4))
		size = 4;
	if ((ptr = ft_strchr(tab, buf[0])))
		idx[0] = ptr - tab;
	else
		return ;
	if ((ptr = ft_strchr(tab, buf[1])))
		idx[1] = ptr - tab;
	else
		idx[1] = 0;
	if ((ptr = ft_strchr(tab, buf[2])))
		idx[2] = ptr - tab;
	else
		idx[2] = 0;
	if ((ptr = ft_strchr(tab, buf[3])))
		idx[3] = ptr - tab;
	else
		idx[3] = 0;
	val[0] = (idx[0] << 2) + ((idx[1] & 0x30) >> 4);
	val[1] = ((idx[1] & 0xF) << 4) + ((idx[2] & 0x3C) >> 2);
	val[2] = idx[3] + ((idx[2] & 0x3) << 6);
	ft_fdprintf(base->fd_o, "%c%c%c", val[0], val[1], val[2]);
	ft_bzero(buf, 64);
}

void base64_decode_encode(char *tab, t_base64 *base, uint32_t opts)
{
	char buf[64];
	int buf_size;
	int len;
	int read_size = ((opts & OPT_D)) ? 4 : 48;

	len = 0;
	ft_bzero(buf, 64);
	while ((buf_size = read(base->fd_i, &buf, read_size)) >
			((base->fd_i != 0) ? (read_size - 1) : 0))
		((opts & OPT_D)) ? b64_decode(base, buf, buf_size, tab)
			: b64_encode(base, buf, buf_size, tab);
	if (buf_size > 0)
		((opts & OPT_D)) ? b64_decode(base, buf, buf_size, tab)
			: b64_encode(base, buf, buf_size, tab);
}
int		process_base64(t_arg *arg, uint32_t opts)
{
	t_base64	*base;
	static char tab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
						"0123456789+/";

	base = (t_base64 *)arg->base;
	if ((base->fd_i = get_input_file(base->input)) < 0
	|| (base->fd_o = get_output_file(base->output)) < 0)
	{
		close_fds(base);
		return (1);
	}
	base64_decode_encode(tab, base, opts);
	close_fds(base);
	return (0);
}
