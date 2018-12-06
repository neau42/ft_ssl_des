/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/06 10:31:00 by nboulaye         ###   ########.fr       */
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
		else if (arg->type == FILE_TYPE)
			ft_printf("[%d]: type: '%s', str: '%s'\n", i++, "FILE", arg->str);
		else if (arg->type == STRING_TYPE)
			ft_printf("[%d]: type: '%s', str: '%s'\n", i++, "STING", arg->str);
		else if (arg->type == BASE64_TYPE)
		{
			ft_printf("[%d]: type: '%s', str: '%s'\n", i++, "BASE64", arg->str);
			ft_printf("->input : '%s'\n", ((t_base64 *)arg->base)->input);
			ft_printf("->output: '%s'\n", ((t_base64 *)arg->base)->output);
		}
		else if (arg->type == DES_TYPE)
		{
			ft_printf("[%d]: type: '%s', str: '%s'\n", i++, "DES", arg->str);
			ft_printf("->input : '%s'\n", ((t_des *)arg->base)->input);
			ft_printf("->output: '%s'\n", ((t_des *)arg->base)->output);
			ft_printf("->pass: '%s'\n", ((t_des *)arg->base)->pass);
			ft_printf("->key: '%s'\n", ((t_des *)arg->base)->key);
			ft_printf("->vector: '%s'\n", ((t_des *)arg->base)->vector);
			ft_printf("->salt: '%s'\n", ((t_des *)arg->base)->salt);
		}

		arg = arg->next;
	}
	ft_printf("opts:   \n%0.32b\nHASH: ", opts);
	if (((opts) & GET_HASH) == OPT_MD5) ft_printf("MD5 ");
	if (((opts) & GET_HASH) == OPT_SHA256) ft_printf("SHA256 ");
	if (((opts) & GET_HASH) == NULL_HASH) ft_printf("NULL ");
	if (((opts) & GET_HASH) == OPT_BASE64) ft_printf("BASE64 ");
	if (((opts) & GET_HASH) == OPT_DES) ft_printf("DES ");
	if (((opts) & GET_HASH) == OPT_ECB) ft_printf("ECB ");
	if (((opts) & GET_HASH) == OPT_CBC) ft_printf("CBC ");
	ft_printf("opts:");
	if (opts & OPT_A) ft_printf(" - A");
	if (opts & OPT_D) ft_printf(" - D");
	if (opts & OPT_DD) ft_printf(" - DD");
	if (opts & OPT_E) ft_printf(" - E");
	if (opts & OPT_H) ft_printf(" - H");
	if (opts & OPT_I) ft_printf(" - I");
	if (opts & OPT_K) ft_printf(" - K");
	if (opts & OPT_O) ft_printf(" - O");
	if (opts & OPT_P) ft_printf(" - P");
	if (opts & OPT_Q) ft_printf(" - Q");
	if (opts & OPT_R) ft_printf(" - R");
	if (opts & OPT_S) ft_printf(" - S");
	if (opts & OPT_V) ft_printf(" - V");
	ft_printf("\n");
}

t_chksum	process_des_ecb(t_arg *arg, uint32_t opts, uint8_t print)
{
	(void)arg;
	(void)opts;
	(void)print;
	ft_printf("process_desECB\n");
	return((t_chksum)0);
}

t_chksum	process_des_cbc(t_arg *arg, uint32_t opts, uint8_t print)
{
	(void)arg;
	(void)opts;
	(void)print;
	ft_printf("process_des CBC\n");
	return ((t_chksum)0);
}


void	parse_args(t_arg *arg, uint32_t opts)
{
	t_arg		*first;
	static t_chksum (*fcts[7])(t_arg * arg, uint32_t, uint8_t) = {
		process_stdin, process_file, process_string, process_base64,
		process_des, process_des_ecb, process_des_cbc};

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

int		main(int ac, char **av)
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
		print_arg(arg, opts);
		rm_arg(arg);
		return (1);
	}
	// print_arg(arg, opts);
	parse_args(arg, opts);
	rm_arg(arg);
	return (0);
}
