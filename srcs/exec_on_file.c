/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_on_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/20 08:36:36 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
void read_stdin(uint32_t opts);
int		    ft_exec_on_null(char *str, uint32_t opts)
{
	(void)str;
		ft_printf("ft_exec_on_null\n");
	if (!(opts & OPT_FILE) || opts & OPT_P)
	{
		ft_printf("\tread stdin\n");
		read_stdin(opts);
	}
	return (0);
}


void format_string(uint8_t *buf, int len, uint64_t nb_loop, uint32_t opts)
{
	uint64_t size;
	
    (void)opts;
	size = nb_loop * SIZE_BUF + len;
	ft_printf("size: %llu\n",size);
	buf[len] = 1;
	while (++len <= (int)(SIZE_BUF - sizeof(uint64_t)))
		buf[len] = 0;
	*(uint64_t *)((uint8_t *)(buf) + len - 1) = size;//endian_swapp(size) ??
	print_memory_hex(buf, SIZE_BUF);
}

int		    ft_exec_on_file(char *file_name, uint32_t opts)
{
	int			i;
	int			fd;
	int			len;
	uint8_t		buf[64];	// (512 / 8)
	uint8_t		result[16];	// (128 / 8)

    (void)opts;
	ft_printf("ft_exec_on_file\n");
	ft_printf("\tEXEC FILE on '%s'\n", file_name);
	fd = (file_name) ? open(file_name, O_RDONLY) : 0;
	if (fd < 0)
	{
		ft_printf("%s: No such file or directory\n",file_name);
		return (-1);
	}
	i = 0;
	while ((len = read(fd, &buf, SIZE_BUF)) > 0)
	{
		if (fd > 0 && len < (int)(SIZE_BUF - sizeof(uint64_t) - 1))
			break ;
		ft_printf(">>>> buf[%d] >>>>>>>>", len);
		print_memory_hex(buf, len);
		ft_printf("<<<< end <<<<\n");
		i++;
	}
	format_string(buf, len, i, opts);
	result[0] = buf[0];
	if (fd > 0)
		close(fd);
	return (0);
}


void read_stdin(uint32_t opts)
{
		int			i;
	int			len;
	uint8_t		buf[64];	// (512 / 8)
	// uint8_t		tmpbuf[64];	// (512 / 8)
	uint8_t		result[16];	// (128 / 8)

    (void)opts;
	ft_printf("read stdin\n");
	i = 0;
	while ((len = read(0, &buf, SIZE_BUF)) > 0)
	{
		ft_printf(">>>> buf[%d] >>>>>>>>", len);
		print_memory_hex(buf, len);
				//pseudo strncat(buf, tmp_bul, 64)
		//if len == 64 exec_algo
		//else concate
		ft_printf("<<<< end <<<<\n");
		i++;
	}
	format_string(buf, len, i, opts);
	result[0] = buf[0];
	return ;
}

