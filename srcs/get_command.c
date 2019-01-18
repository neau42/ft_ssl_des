/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:27:56 by no                #+#    #+#             */
/*   Updated: 2019/01/18 16:42:48 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	get_h_opt_n_err(char *str, uint32_t *opts)
{
	if (str[0] == '-' && ft_strchr(str, 'h'))
		*opts |= OPT_H;
	else
		ft_fdprintf(2, "ft_ssl: '%s' is an invalid command.\n", str);
	*opts |= NULL_HASH;
}

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
	else if (!ft_strcmp(str, "DES-CFB") || !ft_strcmp(str, "des-cfb"))
		*opts |= OPT_CFB;
	else if (!ft_strcmp(str, "DES-OFB") || !ft_strcmp(str, "des-ofb"))
		*opts |= OPT_OFB;
	else if (!ft_strcmp(str, "DES-CTR") || !ft_strcmp(str, "des-ctr"))
		*opts |= OPT_CTR;
	else if (!ft_strcmp(str, "DES-PCBC") || !ft_strcmp(str, "des-pcbc"))
		*opts |= OPT_PCBC;
	else
		get_h_opt_n_err(str, opts);
	return (*opts);
}

t_arg		*arg_error(uint32_t *opts, char *str, t_arg *first)
{
	(*opts) |= OPT_ERR;
	ft_fdprintf(2, "invalid option -- \"%s\"\n", str);
	return (first);
}
