/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_base64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/01 08:45:52 by no               ###   ########.fr       */
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
			ft_fdprintf(2, "ft_ssl: %s: can't be create\n", file_name);
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

void	print_n_init_static(t_base64 *base, uint8_t *val, int *i)
{
	if (*i >= 1)
		ft_fdprintf(base->fd_o, "%c", val[0]);
	if (*i >= 2)
		ft_fdprintf(base->fd_o, "%c", val[1]);
	if (*i >= 3)
		ft_fdprintf(base->fd_o, "%c", val[2]);
	*i = 0;
	val[0] = 0;
	val[1] = 0;
	val[2] = 0;
}

void 	get_b64_decode_value(t_base64 * base, uint8_t idx, int op)
{
	static uint8_t	val[3] = {0};
	static int		i = 0;

	if (op)
	{
		i-=1;
		print_n_init_static(base, val, &i);	
	}
	else if (i == 3)
	{
		val[2] += idx;
		print_n_init_static(base, val, &i);	
	}
	else if (i == 2)
	{
		val[1] += ((idx & 0x3C) >> 2);
		val[i++] = ((idx & 0x3) << 6);
	}
	else if (i == 1)
	{
		val[0] += ((idx & 0x30) >> 4);
		val[i++] = ((idx & 0xF) << 4);
	}
	else if (i == 0)
		val[i++] = (idx << 2);
}


int		get_one_chars(t_base64 *base, char c, char *tab)
{
	char			*ptr;

	if (!c)
		return (1);
	else if (ft_isspace(c))
		;
	else if (c == '=')
	{
		get_b64_decode_value(base, 0, 1);
		ft_fdprintf(2, "11return   pour c : '%c'(%u)\n",c, c); 
		return (1);
	}
	else if ((ptr = ft_strchr(tab, c)))
		get_b64_decode_value(base, ptr - tab, 0);
	else
	{
		ft_fdprintf(2, "22return   pour c : '%c'(%u)\n",c, c); 
		return (1);
	}
	return (0);
}

void b64_decode(t_base64 *base, char *buf, int size, char *tab)//bufsize = 4
{
	int i = 0;

	while (i < size)
	{
		if (get_one_chars(base, buf[i], tab))
			return ;
		i++;
	}
}

int		valid_chunk(char *buf, int *len, char *tab)
{
	int i = -1;
	char *ptr;

	while (++i < *len)
	{
		if (ft_isspace(buf[i]) || buf[i] == '=')
			;
		else if (!(ptr = ft_strchr(tab, buf[i])))
		{
			ft_fdprintf(2, "not valide: '%c'\n", buf[i]);
			return (0);
		}
	}
	return (1);


}

void	read_to_decode(char *tab, t_base64 *base)
{
	char	buf[64];
	int		buf_size;
	int		len;
	int		read_size;
	int		i;

	len = 0;
	i = 0;
	read_size = 64;
	ft_bzero(buf, 64);
	while ((buf_size = read(base->fd_i, &buf, read_size)) > 0)
	{
		// ft_printf("read loop\n");
		if (valid_chunk(buf, &buf_size, tab))
			b64_decode(base, buf, buf_size, tab);
		ft_bzero(buf, 4);
		i++;
	}
}

void read_to_encode(char *tab, t_base64 *base)
{
	char buf[64];
	int buf_size;
	int len;
	int read_size = 48;

	len = 0;
	ft_bzero(buf, 64);
	while ((buf_size = read(base->fd_i, &buf, read_size)) > 0)
		b64_encode(base, buf, buf_size, tab);
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
	((opts & OPT_D)) ? read_to_decode(tab, base) : read_to_encode(tab, base);
	close_fds(base);
	return (0);
}
