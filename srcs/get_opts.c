/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:56:14 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/19 23:50:50 by nboulaye         ###   ########.fr       */
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

static t_data	*get_string(char *str, t_data *data, uint32_t *opts)
{
	if (!str)
	{
		(*opts) |= OPT_ERR;
		return (NULL);
	}
	data->type = STRING_TYPE;
	if (!(data->str = ft_strdup(str)))
		return (NULL);
	data->next = init_data();
	return (data->next);
}

t_data			*get_opts(char *str, char *str_next, uint32_t *opts,
				t_data *data)
{
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
		else if (*str == 's')
			data = get_string(str_next, data, opts);
		else if (*str)
		{
			(*opts) |= OPT_ERR;
			ft_printf("invalid option -- \"%s\"\n", str);
		}
		if (!data || *opts & OPT_ERR)
			break ;
		str++;
	}
	return (data);
}
