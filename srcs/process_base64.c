/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_base64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/27 18:44:40 by no               ###   ########.fr       */
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
			ft_fdprintf(2, "ft_ssl: %s: open INPUT\n", file_name);
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
			ft_fdprintf(2, "ft_ssl: %s: open OUTPUT\n", file_name);
	}
	else
		fd = STDOUT_FILENO;
	return (fd);
}

void close_fds(t_base64 *base)
{
	if (base->fd_i != STDIN_FILENO)
		close(base->fd_i);
	if (base->fd_o > STDOUT_FILENO)
		close(base->fd_o);
}

int		process_base64(t_arg *arg, uint32_t opts)
{
	t_base64	*base;

	ft_printf("process_base64\n");
	base = (t_base64 *)arg->base;
	if ((base->fd_i = get_input_file(base->input) < 0)
	|| (base->fd_o = get_output_file(base->output)) < 0)
	{
		close_fds(base);
		return (1);
	}

	(void)opts;
	close_fds(base);
	return (0);
}
