/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:56:14 by nboulaye          #+#    #+#             */
/*   Updated: 2019/01/17 18:23:22 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			ft_opt_err(uint32_t *opts, char *str)
{
	(*opts) |= OPT_ERR;
	ft_fdprintf(2, "Invalid option -- \"%s\"\n", str);
}

char			*ft_cpy_string(char *old_str, char *new_str, uint32_t *opts)
{
	char	*ptr;

	ptr = NULL;
	if (old_str)
		free(old_str);
	if (new_str)
		ptr = ft_strdup(new_str);
	if (!ptr)
		*opts |= OPT_ERR;
	return (ptr);
}

void			get_base64_option(char *str, char *str_next, uint32_t *opts,
				t_base *b)
{
	t_base64 *base;

	base = (t_base64 *)b;
	if (*str == 'h')
		(*opts) |= OPT_H;
	else if (*str == 'd' && (*opts &= (0xFFFFFFFF ^ OPT_E)))
		(*opts) |= OPT_D;
	else if (*str == 'e' && (*opts &= (0xFFFFFFFF ^ OPT_D)))
		(*opts) |= OPT_E;
	else if (*str == 'i' && (*opts |= (OPT_I | OPT_S)))
		base->input = ft_cpy_string(base->input, str_next, opts);
	else if (*str == 'o' && (*opts |= (OPT_O | OPT_S)))
		base->output = ft_cpy_string(base->output, str_next, opts);
	else if (*str)
		ft_opt_err(opts, str);
	if (str[1])
		ft_opt_err(opts, str);
}

void			get_des_option2(char *str, char *str_next, uint32_t *opts,
						t_des *base)
{
	if (*str == 'o' && (*opts |= (OPT_O | OPT_S)))
		base->output = ft_cpy_string(base->output, str_next, opts);
	else if (*str == 'k' && (*opts |= (OPT_K | OPT_S)))
		base->key = ft_cpy_string(base->key, str_next, opts);
	else if (*str == 'p' && (*opts |= (OPT_P | OPT_S)))
		base->pass = ft_cpy_string(base->pass, str_next, opts);
	else if (*str == 's' && (*opts |= (OPT_S | OPT_S)))
		base->salt = ft_cpy_string(base->salt, str_next, opts);
	else if (*str == 'v' && (*opts |= (OPT_V | OPT_S)))
		base->vector = ft_cpy_string(base->vector, str_next, opts);
	else if (*str)
		ft_opt_err(opts, str);
}

void			get_des_option(char *str, char *str_next, uint32_t *opts,
						t_base *b)
{
	t_des	*base;

	base = (t_des *)b;
	if (*str == 'h')
		(*opts) |= OPT_H;
	else if (*str == 'a')
		(*opts) |= OPT_A;
	else if (*str == 'd' && (*opts &= (0xFFFFFFFF ^ OPT_E)))
		(*opts) |= OPT_D;
	else if (*str == 'e' && (*opts &= (0xFFFFFFFF ^ OPT_D)))
		(*opts) |= OPT_E;
	else if (*str == 'P')
		(*opts) |= OPT_PP;
	else if (*str == 'i' && (*opts |= (OPT_I | OPT_S)))
		base->input = ft_cpy_string(base->input, str_next, opts);
	else if (*str)
		get_des_option2(str, str_next, opts, base);
	if (str[1])
		ft_opt_err(opts, str);
}
