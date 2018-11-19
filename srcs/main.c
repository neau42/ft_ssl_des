/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:56:19 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/19 23:53:28 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void print_data(t_data *data, uint32_t opts)
{
	t_data *first;
	int i = 0;

	first = data;
	ft_printf("data:\n");
	while (data)
	{
		if (data->type == NULL_TYPE)
			ft_printf("[%d]: type: 'NULL_TYPE', str: '%s'\n", i++, data->str);
		else
			ft_printf("[%d]: type: '%s', str: '%s'\n", i++, data->type == FILE_TYPE ? "FILE" : "STING", data->str);
		data = data->next;
	}
	ft_printf("opts: %0.32b\n", opts);
	if (GET_OPT_HASH_TYPE(opts) & MD5_HASH)
		ft_printf("HASH MD5 ");
	else if (GET_OPT_HASH_TYPE(opts) & SHA256_HASH)
		ft_printf("HASH SHA256 ");
	else if (GET_OPT_HASH_TYPE(opts) & NULL_HASH)
		ft_printf("HASH NULL ");
	if (opts & OPT_H) ft_printf("opts H ");
	if (opts & OPT_P) ft_printf("opts P ");
	if (opts & OPT_Q) ft_printf("opts Q ");
	if (opts & OPT_R) ft_printf("opts R ");
	if (opts & OPT_S) ft_printf("opts S ");
	printf("\n");
}

int main(int ac, char **av)
{
	t_data		*data;
	uint32_t	opts;

	data = get_args(ac, av, &opts);
	if (opts & OPT_ERR)
	{
		short_usage(av[0]);
		rm_data(data);
		return (1);
	}

	print_data(data, opts);
	rm_data(data);
	return (0);
}