/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:27:56 by no                #+#    #+#             */
/*   Updated: 2019/01/17 18:41:02 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	get_command(char *str, uint32_t *opts)
{
	if (!ft_strcmp(str, "MD5") || !ft_strcmp(str, "md5"))
		*opts |= OPT_MD5;
	else if (!ft_strcmp(str, "SHA256") || !ft_strcmp(str, "sha256"))
		*opts |= OPT_SHA256;
	else if (!ft_strcmp(str, "BASE64") || !ft_strcmp(str, "base64"))
		*opts |= OPT_BASE64;
	else if (!ft_strcmp(str, "DES") || !ft_strcmp(str, "des"))
		*opts |= OPT_DES;
	else if (!ft_strcmp(str, "DES-ECB") || !ft_strcmp(str, "des-ecb"))
		*opts |= OPT_ECB;
	else if (!ft_strcmp(str, "DES-CBC") || !ft_strcmp(str, "des-cbc"))
		*opts |= OPT_CBC;
	else
	{
		if (str[0] == '-' && ft_strchr(str, 'h'))
			*opts |= OPT_H;
		else
			ft_fdprintf(2, "ft_ssl: '%s' is an invalid command.\n", str);
		*opts |= NULL_HASH;
	}
	return (*opts);
}

t_arg		*arg_error(uint32_t *opts, char *str, t_arg *first)
{
	(*opts) |= OPT_ERR;
	ft_fdprintf(2, "invalid option -- \"%s\"\n", str);
	return (first);
}
