/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_md_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:56:14 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/17 18:23:39 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static t_arg	*get_string(char *str, t_arg *arg, uint32_t *opts,
								uint32_t actual_opts)
{
	if (!str)
	{
		*opts |= OPT_ERR;
		return (NULL);
	}
	*opts |= OPT_S;
	if (actual_opts & OPT_S)
		arg->type = STRING_TYPE;
	else
		arg->type = FILE_TYPE;
	if (!(arg->str = ft_strdup(str)))
		return (NULL);
	arg->next = init_arg();
	return (arg->next);
}

t_arg			*get_md_option(char *str, char *str_next, uint32_t *opts,
				t_arg *arg)
{
	if (*str == 'h')
		(*opts) |= OPT_H;
	else if (*str == 'D')
		(*opts) |= OPT_DD;
	else if (*str == 'p')
		(*opts) |= OPT_P;
	else if (*str == 'q')
		(*opts) |= OPT_Q;
	else if (*str == 'r')
		(*opts) |= OPT_R;
	else if (*str == 's' && !(*opts & OPT_S))
		arg = get_string(str_next, arg, opts, OPT_S);
	else if (*str)
		ft_opt_err(opts, str);
	if (str[1])
		ft_opt_err(opts, str);
	return (arg);
}
