/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 02:24:01 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_arg(t_arg *arg, uint32_t opts)
{
	t_arg	*first;
	int 	i = 0;

	first = arg;
	ft_printf("arg:\n");
	while (arg)
	{
		if (arg->type == NULL_TYPE)
			ft_printf("[%d]: type: 'NULL_TYPE', str: '%s'\n", i++, arg->str);
		else
			ft_printf("[%d]: type: '%s', str: '%s'\n", i++, arg->type == FILE_TYPE ? "FILE" : "STING", arg->str);
		arg = arg->next;
	}
	ft_printf("opts:   \n%0.32b\n", opts);
	if (opts & MD5_HASH)
		ft_printf("HASH MD5 ");
	else if (opts & SHA256_HASH)
		ft_printf("HASH SHA256 ");
	else if (opts & NULL_HASH)
		ft_printf("HASH NULL ");
		ft_printf("opts:");
	if (opts & OPT_H) ft_printf(" H");
	if (opts & OPT_P) ft_printf(" P");
	if (opts & OPT_Q) ft_printf(" Q");
	if (opts & OPT_R) ft_printf(" R");
	if (opts & OPT_S) ft_printf(" S");
	printf("\n");
}

void	parse_args(t_arg *arg, uint32_t opts)
{
	t_arg *first;
	static int (*fcts[3])(char *, uint32_t ) = {
		process_null, process_file, process_string};

	first = arg;
	while (arg)
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
		return 1;
	}
	arg = get_args(ac, av, &opts);
	if (opts & (OPT_ERR | OPT_H | NULL_HASH))
	{
		(opts & OPT_H) ? long_usage(av[0]) : short_usage(av[0]);
		rm_arg(arg);
		return (1);
	}
	parse_args(arg, opts);
	// print_arg(arg, opts);
	rm_arg(arg);
	return (0);
}