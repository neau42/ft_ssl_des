/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:27:56 by no                #+#    #+#             */
/*   Updated: 2018/11/26 04:25:44 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		short_usage(char *str)
{
	ft_fdprintf(2, "usage:\n%s <md5|sha256|des|des-ecb|des-cbc> "
	"[options] file ...\n", str);
}

static void 	usage_option(void)
{
	ft_fdprintf(2, "\n\nCipher options:"
	"\nbase64:"
	"\n -d: decode mode."
	"\n -e: encode mode."
	"\n -i: input file."
	"\n -o: output file."
	"\ndes*:"
	"\n -a: decode/encode the input/output in base64,"
				"depending on the encrypt mode."
	"\n -d: decrypt mode."
	"\n -e: encrypt mode (default)."
	"\n -i: input file for message."
	"\n -k: key in hex is the next arguement."
	"\n -o: output file for message."
	"\n -p: password in ascii is the next argument."
	"\n -s: the salt in hex is the next argument."
	"\n -v: initialization vector in hex is the next argument."
	"\n");
}

void		long_usage(char *str)
{
	short_usage(str);
	ft_fdprintf(2, "Standard commands:"
	"\n\nStandard options:"
	"\n -h: help."
	"\n\nMessage Digest commands:"
	"\n md5: to use the md5 message digest algorithm."
	"\n sha256: to use the sha256 message digest algorithm."
	"\n\nMessage Digest options:"
	"\n -D: debug, print chuck."
	"\n -p: echo STDIN to STDOUT and append the checksum to STDOUT."
	"\n -q: quiet mode."
	"\n -r: reverse the format of the output."
	"\n -s: print the sum of the given string."
	"\n\nCipher commands:"
	"\n base64"
	"\n des"
	"\n des-ecb"
	"\n des-cbc");
	usage_option();
}
