/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/25 02:38:42 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	parse_args(t_arg *arg, uint32_t opts)
{
	t_arg		*first;
	static int	(*fcts[3])(char *, uint32_t) = {
		process_stdin, process_file, process_string};

	first = arg;
	if (opts & OPT_P || !arg->type)
	{
		fcts[0](arg->str, opts);
		opts |= OPT_FILE;
	}
	while (arg && arg->type)
	{
		fcts[(int)arg->type](arg->str, opts);
		arg = arg->next;
	}
}

int		main(int ac, char **av)
{
	t_arg		*arg;
	uint32_t	opts;

	if (ac < 2)
	{
		short_usage(av[0]);
		return (1);
	}
	arg = get_args(ac, av, &opts);
	if (opts & (OPT_ERR | OPT_H) || (opts & GET_HASH) == NULL_HASH)
	{
		(opts & OPT_H) ? long_usage(av[0]) : short_usage(av[0]);
		rm_arg(arg);
		return (1);
	}
	parse_args(arg, opts);
	rm_arg(arg);
	return (0);
}
