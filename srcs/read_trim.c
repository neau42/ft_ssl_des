/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_trim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 18:39:44 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/16 16:11:24 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static size_t	rm_space(char *str, size_t size)
{
	size_t final_size;

	final_size = size;
	while (size--)
	{
		if (ft_isspace(*str))
		{
			if (size)
				ft_memmove(str, &str[1], size);
			str[size] = 0;
			final_size--;
		}
		else
			str++;
	}
	return (final_size);
}

int				read_trim(int fd, char *buf, size_t size)
{
	size_t	final_size;
	ssize_t	tmp_size;

	final_size = 0;
	while (final_size < size)
	{
		tmp_size = read(fd, &buf[final_size], size - final_size);
		if (tmp_size < 0)
			return (-1);
		if (tmp_size == 0)
			return (final_size);
		final_size += rm_space(&buf[final_size], tmp_size);
	}
	return (final_size);
}
