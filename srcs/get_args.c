/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:27:56 by no                #+#    #+#             */
/*   Updated: 2018/11/25 09:11:51 by no               ###   ########.fr       */
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

static uint32_t	set_hash_type(char *str, uint32_t *opts)
{
	if (!ft_strcmp(str, "MD5") || !ft_strcmp(str, "md5"))
		*opts |= OPT_MD5;
	else if (!ft_strcmp(str, "SHA256") || !ft_strcmp(str, "sha256"))
		*opts |= OPT_SHA256;
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
	if (set_hash_type(av[1], opts) & NULL_HASH)
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
