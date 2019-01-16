/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/16 15:46:32 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_chksum	process_des_cbc(t_arg *arg, uint32_t opts, uint8_t print)
{
	(void)arg;
	(void)opts;
	(void)print;
	ft_printf("process_des CBC\n");
	return ((t_chksum)0);
}

void		parse_args(t_arg *arg, uint32_t opts)
{
	t_arg					*first;
	static		t_chksum	(*fcts[7])(t_arg *arg, uint32_t, uint8_t) = {
	process_stdin, process_file, process_string, process_base64,
	process_des_cbc, process_des_ecb, process_des_cbc};

	first = arg;
	if ((arg->type <= STRING_TYPE && (opts & OPT_P)) || !arg->type)
	{
		fcts[0](arg, opts, 1);
		opts |= OPT_FILE;
	}
	while (arg && arg->type)
	{
		fcts[(int)arg->type](arg, opts, 1);
		arg = arg->next;
	}
}

int			main(int ac, char **av)
{
	t_arg		*arg;
	uint32_t	opts;

	if (ac < 2)
	{
		short_usage(av[0]);
		return (1);
	}
	srand((uint32_t)&main);
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
