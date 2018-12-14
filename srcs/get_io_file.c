/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_io_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/14 17:49:19 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		open_error(int fd, char *file_name)
{
	struct stat	stat;

	if (fd < 0)
		ft_fdprintf(2, "ft_ssl: %s: %s\n", file_name, strerror(errno));
	else if (fstat(fd, &stat))
		ft_fdprintf(2, "ft_ssl: %s: No such file or directory\n", file_name);
	else if (S_ISDIR(stat.st_mode))
		ft_fdprintf(2, "ft_ssl: %s: is a directory\n", file_name);
	else
		return (0);
	return (1);
}

int get_input_file(char *file_name)
{
	int			fd;

	if (file_name)
	{
		errno = 0;
		fd = open(file_name, O_RDONLY);
		if (open_error(fd, file_name))
			return (-1);
		return (fd);
	}
	return (STDIN_FILENO);
}

int		get_output_file(char *file_name)
{
	int fd;

	if (file_name)
	{
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			ft_fdprintf(2, "ft_ssl: %s: can't be create\n", file_name);
	}
	else
		fd = STDOUT_FILENO;
	return (fd);
}
