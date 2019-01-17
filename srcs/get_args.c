/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:27:56 by no                #+#    #+#             */
/*   Updated: 2019/01/17 19:11:07 by nboulaye         ###   ########.fr       */
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

t_base			*init_base(uint32_t *opts, t_arg *arg)
{
	if ((*opts & GET_HASH) == OPT_BASE64)
	{
		arg->type = BASE64_TYPE;
		return ((t_base *)ft_memalloc(sizeof(t_base64)));
	}
	else if ((*opts & GET_HASH) >= OPT_DES)
	{
		arg->type = DES_TYPE;
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
