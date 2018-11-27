/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:27:56 by no                #+#    #+#             */
/*   Updated: 2018/11/27 04:31:39 by nboulaye         ###   ########.fr       */
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
	arg->base = NULL;
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

t_arg *arg_error(uint32_t *opts, char *str, t_arg *first)
{
	(*opts) |= OPT_ERR;
	ft_fdprintf(2, "invalid option -- \"%s\"\n", str);
	return (first);
}

t_base		*init_base(uint32_t *opts, t_arg *arg)
{
	if ((*opts & GET_HASH) == OPT_BASE64)
	{
		arg->type = BASE64_TYPE;
		return ((t_base *)ft_memalloc(sizeof(t_base64)));
	}
	else if ((*opts & GET_HASH) == OPT_DES)
	{
		arg->type = DES_TYPE;
		return ((t_base *)ft_memalloc(sizeof(t_des)));
	}
	else if ((*opts & GET_HASH) == OPT_ECB)
	{
		arg->type = ECB_TYPE;
		return ((t_base *)ft_memalloc(sizeof(t_des)));
	}
	else if ((*opts & GET_HASH) == OPT_CBC)
	{
		arg->type = CBC_TYPE;
		return ((t_base *)ft_memalloc(sizeof(t_des)));
	}
	*opts |= OPT_ERR;
	return (NULL);
}

t_arg			*get_base_opts(int ac, char **av, uint32_t *opts, t_arg *arg)
{
	int			i;
	static void	(*fcts[4])(char *, char *, uint32_t *, t_base *) = {
		get_base64_option,
		get_des_option,
		get_des_option,
		get_des_option };

	i = 1;
	if (!(arg->base = init_base(opts, arg)))
		return (arg);
	while (++i < ac)
	{
		if (av[i][0] != '-'
		|| (!av[i][1] || (av[i][1] == '-' && !av[i][2] && ++i)))
			break ;
		fcts[(GET_HASH & *opts) - OPT_BASE64](&av[i][1], av[i + 1],
											opts, (t_base*)arg->base);
		if (*opts & OPT_ERR)
			return (arg);
		else if (*opts & OPT_S && i++)
			*opts ^= OPT_S;
	}
	if (i < ac)
		return (arg_error(opts, av[i], arg));
	return (arg);
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
	if (((*opts) & GET_HASH) >= OPT_BASE64)
		return (get_base_opts(ac, av, opts, first));
	while (++i < ac)
		if (av[i][0] != '-'
		|| (!av[i][1] || (av[i][1] == '-' && !av[i][2] && ++i)))
			break ;
		else if (!(arg = get_md_option(&av[i][1], av[i + 1], opts, arg))
		|| *opts & OPT_ERR)
			return (first);
		else if (*opts & OPT_S && i++)
			*opts ^= OPT_S;
	while (i < ac)
		arg = get_file_name(arg, av[i++], opts);
	return (first);
}
