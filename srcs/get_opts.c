/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:56:14 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/22 23:43:21 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// static uint32_t	get_opt_int(char **str)
// {
// 	uint32_t	count;

// 	(*str)++;
// 	while (**str && **str == ' ')
// 		(*str)++;
// 	if ((count = ft_atoi(*str)))
// 	{
// 		while (ft_isdigit(**str))
// 			(*str)++;
// 		(*str)--;
// 	}
// 	return (count);
// }

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
