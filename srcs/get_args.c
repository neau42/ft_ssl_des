/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:27:56 by no                #+#    #+#             */
/*   Updated: 2018/11/19 20:18:50 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void 		short_usage(char *str)
{
	ft_printf("usage:\n%s <md5|sha-256> [-hpqrs] \n", str);
}

void		long_usage(char *str)
{
	short_usage(str);
}

t_data		*init_data(void)
{
	t_data *data;

	if (!(data = ft_memalloc(sizeof(t_data))))
		return (NULL);
	data->type = NULL_TYPE;
	data->str = NULL;
	data->next = NULL;
	return (data);
}

t_data		*get_file_name(t_data *data, char *name_file)
{
	data->type = FILE_TYPE;
	if (!(data->str = ft_strdup(name_file)))
		return (NULL);
	data->next = init_data();
	return (data->next);
}

int			get_hash_type(char *str)
{
	if (!ft_strcmp(str, "MD5") || !ft_strcmp(str, "md5"))
		return (MD5_HASH);
	if (!ft_strcmp(str, "SHA256") || !ft_strcmp(str, "sha256"))
		return (SHA256_HASH);
	ft_printf("bad type: '%s'\n", str);
	return (NULL_HASH);
}

t_data		*get_args(int ac, char **av, uint32_t *opts)
{
	int		i;
	t_data	*data;
	t_data	*first;

	i = 1;
	*opts = 0;
	if (ac < 2 || !(data = init_data()))
		return (NULL);
	first = data;
	if ((*opts = SET_OPT_HASH_TYPE(get_hash_type(av[1]))) == NULL_HASH)
		return (NULL);
	while (++i < ac)
	{
		if (av[i][0] != '-'
		|| (!av[i][1] || (av[i][1] == '-' && !av[i][2] && ++i)))
			break ;
		else
		{
			data = get_opts(&av[i][1], av[i + 1], opts, data);
			i++;
		}
		if (*opts & (OPT_ERR))
			break ;
	}
	while (i < ac)
	{
		data = get_file_name(data, av[i]);
		i++;
	}
		return (first);
}
