/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:27:56 by no                #+#    #+#             */
/*   Updated: 2018/11/22 23:42:19 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		short_usage(char *str)
{
	ft_fdprintf(2, "usage:\n%s <md5|sha256> [-hpqrs] file ...\n", str);
}

void		long_usage(char *str)
{
	short_usage(str);
	ft_fdprintf(2, "Message Digest commands:"
	"\n md5: to use the md5 message digest algorithm."
	"\n sha256: to use the sha256 message digest algorithm."
	"\n-h: help."
	"\n-p: echo STDIN to STDOUT and append the checksum to STDOUT."
	"\n-q: quiet mode."
	"\n-r: reverse the format of the output."
	"\n-s: print the sum of the given string."
	"\n");
}
