/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:27:56 by no                #+#    #+#             */
/*   Updated: 2018/11/26 04:05:34 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_arg			*init_arg(void)
{
	t_arg *arg;

	if (!(arg = ft_memalloc(sizeof(t_arg))))
		return (NULL);
	arg->type = NULL_TYPE;
	arg->str = NULL;
	arg->next = NULL;
	return (arg);
}

static t_arg	*get_file_name(t_arg *arg, char *name_file, uint32_t *opts)
{
	arg->type = FILE_TYPE;
	if (!(arg->str = ft_strdup(name_file)))
		return (NULL);
	*opts |= OPT_FILE;
	arg->next = init_arg();
	return (arg->next);
}

static uint32_t	get_command(char *str, uint32_t *opts)
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

t_arg			*get_args(int ac, char **av, uint32_t *opts)
{
	int		i;
	t_arg	*arg;
	t_arg	*first;

	i = 1;
	*opts = 0;
	if (!(arg = init_arg()))
		return (NULL);
	first = arg;
	if ((get_command(av[1], opts) & GET_HASH) == NULL_HASH)
		return (first);
	while (++i < ac)
	{
		if (av[i][0] != '-'
		|| (!av[i][1] || (av[i][1] == '-' && !av[i][2] && ++i)))
			break ;
		arg = get_opts(&av[i][1], av[i + 1], opts, arg);
		if (!arg || *opts & OPT_ERR)
			return (first);
		if (*opts & OPT_S && i++)
			*opts ^= OPT_S;
	}
	while (i < ac)
		arg = get_file_name(arg, av[i++], opts);
	return (first);
}
