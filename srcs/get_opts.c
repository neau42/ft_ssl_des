/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:56:14 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/25 02:30:14 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static t_arg	*get_string(char *str, t_arg *arg, uint32_t *opts)
{
	if (!str)
	{
		*opts |= OPT_ERR;
		return (NULL);
	}
	*opts |= OPT_S;
	arg->type = STRING_TYPE;
	if (!(arg->str = ft_strdup(str)))
		return (NULL);
	arg->next = init_arg();
	return (arg->next);
}

t_arg			*get_opts(char *str, char *str_next, uint32_t *opts,
				t_arg *arg)
{
	int chk;

	chk = 0;
	while (*str)
	{
		if (*str == 'h')
			(*opts) |= OPT_H;
		else if (*str == 'p')
			(*opts) |= OPT_P;
		else if (*str == 'q')
			(*opts) |= OPT_Q;
		else if (*str == 'r')
			(*opts) |= OPT_R;
		else if (*str == 's' && !chk++)
			arg = get_string(str_next, arg, opts);
		else if (*str)
		{
			(*opts) |= OPT_ERR;
			ft_fdprintf(2, "invalid option -- \"%s\"\n", str);
		}
		if (!arg || *opts & OPT_ERR)
			break ;
		str++;
	}
	return (arg);
}
