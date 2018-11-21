/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 01:10:23 by no                #+#    #+#             */
/*   Updated: 2018/11/21 01:41:14 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
static int _md5_errno = MD5_SUCCESS;
static unsigned T[64];
 
static int md5_comput(char * sum, const char * buf, int bytes);
 
int md5_init()
{
    int ret = 0;
    FILE * f = fopen("t.data", "rb");
 
    if (f == NULL)
    {
        ret = -1;
        md5_set_err_number(MD5_INTERNAL_ERROR);
    }
    else
    {
        size_t n = fread(T, sizeof(T[0]), sizeof(T) / sizeof(T[0]), f);
        if (n != 64)
        {
            ret = -1;
            md5_set_err_number(MD5_INTERNAL_ERROR);
        }
        fclose(f);
    }
    return ret;
}
 
int md5(char * sum, const char * m, int bytes) /* Calcule le MD5 d'un message */
{
    int ret = 0;
 
    /* Valider les arguments */
 
    if (sum == NULL || m == NULL || bytes < 0)
    {
        /* Arguments invalides */
 
        ret = -1;
        md5_set_err_number(MD5_INVALID_ARG);
    }
    else
    {
        /* Calculer la memoire necessaire pour la phase initiale */
 
        int N, mod, pad = 0;
        char * M;
 
        N = bytes + 1;
        mod = N % 64;
 
        if (mod != 56)
            pad = (N < 56) ? 56 - mod : 56 + 64 - mod;
 
        M = malloc(bytes + 1 + pad + 8);
 
        if (M == NULL)
        {
            /* Le systeme n'a pas assez de memoire */
 
            ret = -1;
            md5_set_err_number(MD5_NO_MEM);
        }
        else
        {
            /* Normaliser le message */
 
            int64_t n = bytes * 8; /* Longueur du message en bits */
            int N = bytes;
 
            memcpy(M, m, bytes);
 
            M[N] = '\x80'; /* Ajouter "10000000" */
            N++;
 
            if (pad != 0)
            {
                memset(M + N, (unsigned char)0, pad); /* Completer par des "0" */
                N += pad;
            }
 
            memcpy(M + bytes + 1 + pad, &n, sizeof(n)); /* Ajouter "n" */
            N += 8;
 
            /* Calculer le MD5 */
 
            ret = md5_comput(sum, M, N);
 
            free(M);
        }
    }
 
    return ret;
}
 
int md5_comput(char * sum, const char * buf, int bytes) /* Calcule le MD5 d'un message normalise */
{
    int ret = 0;
    const unsigned * M = (const unsigned *)buf;
    int i, N = bytes / 4;
    unsigned r[4] = {A0, B0, C0, D0}; /* Registres A, B, C et D */
 
    for(i = 0; i < N / 16; i++)
    {
        const unsigned * x = (M + (16 * i));
        int j;
        unsigned s[4];
 
        for(j = 0; j < 4; j++)
            s[j] = r[j];
 
        j = 0;
 
        FXT(r[0], r[1], r[2], r[3], x[ 0], S11, T[j]); j++;
        FXT(r[3], r[0], r[1], r[2], x[ 1], S12, T[j]); j++;
        FXT(r[2], r[3], r[0], r[1], x[ 2], S13, T[j]); j++;
        FXT(r[1], r[2], r[3], r[0], x[ 3], S14, T[j]); j++;
        FXT(r[0], r[1], r[2], r[3], x[ 4], S11, T[j]); j++;
        FXT(r[3], r[0], r[1], r[2], x[ 5], S12, T[j]); j++;
        FXT(r[2], r[3], r[0], r[1], x[ 6], S13, T[j]); j++;
        FXT(r[1], r[2], r[3], r[0], x[ 7], S14, T[j]); j++;
        FXT(r[0], r[1], r[2], r[3], x[ 8], S11, T[j]); j++;
        FXT(r[3], r[0], r[1], r[2], x[ 9], S12, T[j]); j++;
        FXT(r[2], r[3], r[0], r[1], x[10], S13, T[j]); j++;
        FXT(r[1], r[2], r[3], r[0], x[11], S14, T[j]); j++;
        FXT(r[0], r[1], r[2], r[3], x[12], S11, T[j]); j++;
        FXT(r[3], r[0], r[1], r[2], x[13], S12, T[j]); j++;
        FXT(r[2], r[3], r[0], r[1], x[14], S13, T[j]); j++;
        FXT(r[1], r[2], r[3], r[0], x[15], S14, T[j]); j++;
 
        GXT(r[0], r[1], r[2], r[3], x[ 1], S21, T[j]); j++;
        GXT(r[3], r[0], r[1], r[2], x[ 6], S22, T[j]); j++;
        GXT(r[2], r[3], r[0], r[1], x[11], S23, T[j]); j++;
        GXT(r[1], r[2], r[3], r[0], x[ 0], S24, T[j]); j++;
        GXT(r[0], r[1], r[2], r[3], x[ 5], S21, T[j]); j++;
        GXT(r[3], r[0], r[1], r[2], x[10], S22, T[j]); j++;
        GXT(r[2], r[3], r[0], r[1], x[15], S23, T[j]); j++;
        GXT(r[1], r[2], r[3], r[0], x[ 4], S24, T[j]); j++;
        GXT(r[0], r[1], r[2], r[3], x[ 9], S21, T[j]); j++;
        GXT(r[3], r[0], r[1], r[2], x[14], S22, T[j]); j++;
        GXT(r[2], r[3], r[0], r[1], x[ 3], S23, T[j]); j++;
        GXT(r[1], r[2], r[3], r[0], x[ 8], S24, T[j]); j++;
        GXT(r[0], r[1], r[2], r[3], x[13], S21, T[j]); j++;
        GXT(r[3], r[0], r[1], r[2], x[ 2], S22, T[j]); j++;
        GXT(r[2], r[3], r[0], r[1], x[ 7], S23, T[j]); j++;
        GXT(r[1], r[2], r[3], r[0], x[12], S24, T[j]); j++;
 
        HXT(r[0], r[1], r[2], r[3], x[ 5], S31, T[j]); j++;
        HXT(r[3], r[0], r[1], r[2], x[ 8], S32, T[j]); j++;
        HXT(r[2], r[3], r[0], r[1], x[11], S33, T[j]); j++;
        HXT(r[1], r[2], r[3], r[0], x[14], S34, T[j]); j++;
        HXT(r[0], r[1], r[2], r[3], x[ 1], S31, T[j]); j++;
        HXT(r[3], r[0], r[1], r[2], x[ 4], S32, T[j]); j++;
        HXT(r[2], r[3], r[0], r[1], x[ 7], S33, T[j]); j++;
        HXT(r[1], r[2], r[3], r[0], x[10], S34, T[j]); j++;
        HXT(r[0], r[1], r[2], r[3], x[13], S31, T[j]); j++;
        HXT(r[3], r[0], r[1], r[2], x[ 0], S32, T[j]); j++;
        HXT(r[2], r[3], r[0], r[1], x[ 3], S33, T[j]); j++;
        HXT(r[1], r[2], r[3], r[0], x[ 6], S34, T[j]); j++;
        HXT(r[0], r[1], r[2], r[3], x[ 9], S31, T[j]); j++;
        HXT(r[3], r[0], r[1], r[2], x[12], S32, T[j]); j++;
        HXT(r[2], r[3], r[0], r[1], x[15], S33, T[j]); j++;
        HXT(r[1], r[2], r[3], r[0], x[ 2], S34, T[j]); j++;
 
        IXT(r[0], r[1], r[2], r[3], x[ 0], S41, T[j]); j++;
        IXT(r[3], r[0], r[1], r[2], x[ 7], S42, T[j]); j++;
        IXT(r[2], r[3], r[0], r[1], x[14], S43, T[j]); j++;
        IXT(r[1], r[2], r[3], r[0], x[ 5], S44, T[j]); j++;
        IXT(r[0], r[1], r[2], r[3], x[12], S41, T[j]); j++;
        IXT(r[3], r[0], r[1], r[2], x[ 3], S42, T[j]); j++;
        IXT(r[2], r[3], r[0], r[1], x[10], S43, T[j]); j++;
        IXT(r[1], r[2], r[3], r[0], x[ 1], S44, T[j]); j++;
        IXT(r[0], r[1], r[2], r[3], x[ 8], S41, T[j]); j++;
        IXT(r[3], r[0], r[1], r[2], x[15], S42, T[j]); j++;
        IXT(r[2], r[3], r[0], r[1], x[ 6], S43, T[j]); j++;
        IXT(r[1], r[2], r[3], r[0], x[13], S44, T[j]); j++;
        IXT(r[0], r[1], r[2], r[3], x[ 4], S41, T[j]); j++;
        IXT(r[3], r[0], r[1], r[2], x[11], S42, T[j]); j++;
        IXT(r[2], r[3], r[0], r[1], x[ 2], S43, T[j]); j++;
        IXT(r[1], r[2], r[3], r[0], x[ 9], S44, T[j]); j++;
 
        for(j = 0; j < 4; j++)
            r[j] += s[j];
    }
 
    memcpy(sum, r, 16);
 
    return ret;
}
 
void md5_format(char * output, const char * sum)
{
    md5_format_ex(output, sum, 16);
}
 
void md5_format_ex(char * output, const char * m, int bytes)
{
    int i;
 
    for(i = 0; i < bytes; i++)
    {
        sprintf(output, "%02x", (unsigned char)m[i]);
        output += 2;
    }
}
 
int md5_get_err_number()
{
    return _md5_errno;
}
 
void md5_set_err_number(int n)
{
    _md5_errno = n;
}