/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:18:48 by nboulaye          #+#    #+#             */
/*   Updated: 2018/11/19 19:17:49 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_printf.h"
# include "libft.h"
# include <stdlib.h>

# define OPT_ERR 0x1
# define OPT_H 0x2
# define OPT_P 0x4
# define OPT_Q 0x8
# define OPT_R 0x10
# define OPT_S 0x20
# define GET_OPT_HASH_TYPE(x) ((x & 0xF0000000) >> 28)
# define SET_OPT_HASH_TYPE(x) ((x & 0xF) << 28)

# define NULL_TYPE 0x0
# define FILE_TYPE 0x1
# define STRING_TYPE 0x2

# define MD5_HASH 0x1
# define SHA256_HASH 0x2
# define NULL_HASH 0x4

typedef struct s_data
{
	char			type;
	char			*str;
	struct s_data	*next;
}				t_data;

t_data	*get_args(int ac, char **av, uint32_t *opts);
t_data	*get_opts(char *str, char *str_next, uint32_t *opts, t_data *data);
t_data	*init_data(void);


#endif
