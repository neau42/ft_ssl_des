/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:56:14 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/26 05:00:04 by nboulaye         ###   ########.fr       */
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
	else if (actual_opts & OPT_S)
		arg->type = FILE_TYPE;
	if (!(arg->str = ft_strdup(str)))
		return (NULL);
	arg->next = init_arg();
	return (arg->next);
}

static void		ft_opt_err(uint32_t *opts, char *str)
{
	(*opts) |= OPT_ERR;
	ft_fdprintf(2, "invalid option -- \"%s\"\n", str);
}

static t_arg	*get_md_option(char *str, char *str_next, uint32_t *opts,
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

t_arg			*get_base64_option(char *str, char *str_next, uint32_t *opts,
				t_arg *arg)
{
	if (*str == 'h')
		(*opts) |= OPT_H;
	else if (*str == 'd' && (*opts ^= OPT_E || 1))
		(*opts) |= OPT_D;
	else if (*str == 'e' && (*opts ^= OPT_D || 1))
		(*opts) |= OPT_E;
	else if (*str == 'i' && (*opts |= OPT_I))
		arg = get_string(str_next, arg, opts, OPT_I);
	else if (*str == 'o' && (*opts |= OPT_O))
		arg = get_string(str_next, arg, opts, OPT_O);
	else if (*str)
		ft_opt_err(opts, str);
	if (str[1])
		ft_opt_err(opts, str);
	(void)str_next;
	return (arg);
}

t_arg			*get_des_option(char *str, char *str_next, uint32_t *opts,
				t_arg *arg)
{
	if (*str == 'h')
		(*opts) |= OPT_H;
	else if (*str == 'a')
		(*opts) |= OPT_A;
	else if (*str == 'd')
		(*opts) |= OPT_D;
	else if (*str == 'e')
		(*opts) |= OPT_E;
	else if (*str == 'i' && (*opts |= OPT_I))
		arg = get_string(str_next, arg, opts, OPT_O);
	else if (*str == 'k')
		(*opts) |= OPT_K;
	else if (*str == 'o' && (*opts |= OPT_O))
		arg = get_string(str_next, arg, opts, OPT_O);
	else if (*str == 'p')
		(*opts) |= OPT_P;
	else if (*str == 's')
		(*opts) |= OPT_S;
	else if (*str == 'v')
		(*opts) |= OPT_V;
	else if (*str)
		ft_opt_err(opts, str);
	if (str[1])
		ft_opt_err(opts, str);
	return (arg);
}

t_arg			*get_opts(char *str, char *str_next, uint32_t *opts,
				t_arg *arg)
{
	static t_arg *(*fcts[7])(char *, char *, uint32_t *, t_arg *) = {
		NULL,
		get_md_option,
		get_md_option,
		get_base64_option,
		get_des_option,
		get_des_option,
		get_des_option };

	return (fcts[((GET_HASH & *opts))](str, str_next, opts, arg));
}
