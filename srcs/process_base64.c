/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_base64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/28 03:00:47 by nboulaye         ###   ########.fr       */
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
		else
			ft_fdprintf(2, "ft_ssl: %s: open INPUT, fd: %d\n", file_name, fd);
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
		else
			ft_fdprintf(2, "ft_ssl: %s: open OUTPUT, fd: %d\n", file_name, fd);
			return (fd);
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

void b64_algo_decode(t_base64 *base, char *buf, int size, char *tab)//bufsize = 4
{
	char val[3];
	char idx[4];

	idx[0] = buf[0];
	idx[1] = buf[1];
	idx[2] = buf[2];
	idx[3] = buf[3];
	// val[1] = 
	// val[2] = 

	// val[0] = (buf[0] >> 2);
	// val[1] = (((buf[0] & 0x3) << 4) + (buf[1] >> 4));
	// val[2] = (((buf[1] & 0x0F) << 2) + (buf[2] >> 6));
	// val[3] = buf[2] & 0x3F;
	int i = -1;
	while (++i < (size + 1))
		ft_fdprintf(base->fd_o, "%c", tab[(int)val[i]]);
	while (size % 4)
	{
		ft_fdprintf(base->fd_o, "=");
		size++;
	}
}

void	b64_algo_encode(t_base64 *base, char *buf, int len, char *tab)//bufsize = 3
{
	char		val[4];
	int			size;

	val[0] = (buf[0] >> 2);
	val[1] = (((buf[0] & 0x3) << 4) + (buf[1] >> 4));
	val[2] = (((buf[1] & 0x0F) << 2) + (buf[2] >> 6));
	val[3] = buf[2] & 0x3F;
	int i = -1;
	if (!(size = len % 3))
		size = 3;
	while (++i < (size + 1))
		ft_fdprintf(base->fd_o, "%c", tab[(int)val[i]]);
	while (size % 3)
	{
		ft_fdprintf(base->fd_o, "=");
		size++;
	}
	if ((len % 16) == 0)
		ft_fdprintf(base->fd_o, "\n");
}

int		process_base64(t_arg *arg, uint32_t opts)
{
	static char tab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
						"0123456789+/";
	t_base64	*base;
	char		buf[10];
	int			buf_size;
	int			len;

	(void)opts;
	len = 0;
	base = (t_base64 *)arg->base;
	if ((base->fd_i = get_input_file(base->input)) < 0
	|| (base->fd_o = get_output_file(base->output)) < 0)
	{
		close_fds(base);
		return (1);
	}
	if (base->fd_i != 0)
		while ((buf_size = read(base->fd_i, &buf, 3)) == 3)
			b64_algo_encode(base, buf, (len += buf_size), tab);
	else
		while ((buf_size = read(base->fd_i, &buf, 3)) > 0)
		{
			if (buf_size < 3)
				buf[buf_size] = 0;
			b64_algo_encode(base, buf, (len += buf_size), tab);
		}
	if (buf_size > 0)
	{
		buf[buf_size] = '\0';
		b64_algo_encode(base, buf, (len += buf_size), tab);
	}
	ft_fdprintf(base->fd_o, "\n");
	close_fds(base);
	return (0);
}
