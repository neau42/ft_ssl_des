/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: no <no@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 01:08:44 by no                #+#    #+#             */
/*   Updated: 2018/11/21 01:26:17 by no               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MD5_MELEM_H
 
#define H_MD5_MELEM_H
 
/* Gestion des erreurs */
 
#define MD5_SUCCEEDED(n) ((n) == 0)
 
enum e_md5_errors {
    MD5_SUCCESS, MD5_INTERNAL_ERROR, MD5_INVALID_ARG, MD5_NO_MEM
};
 
/* Valeurs initiales des registres A, B, C et D */
 
#define A0 0x67452301
#define B0 0xefcdab89
#define C0 0x98badcfe
#define D0 0x10325476
 
/* Definition des macros F, G, H et I */
 
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
 
/* Implementation de l'operateur <<< (rotate left) */
 
#define ROL(x, n) (((x) << (n)) | ((x) >> (32-(n))))
 
/* Definition des macros FXT, GXT, HXT et IXT et des constantes Snn */
 
#define FXT(a, b, c, d, x, s, t) ((a) = (b) + ROL(((a) + F((b), (c), (d)) + (x) + (t)), (s)))
#define GXT(a, b, c, d, x, s, t) ((a) = (b) + ROL(((a) + G((b), (c), (d)) + (x) + (t)), (s)))
#define HXT(a, b, c, d, x, s, t) ((a) = (b) + ROL(((a) + H((b), (c), (d)) + (x) + (t)), (s)))
#define IXT(a, b, c, d, x, s, t) ((a) = (b) + ROL(((a) + I((b), (c), (d)) + (x) + (t)), (s)))
 
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21
 
/* Declaration des fonctions */
 
int  md5_init(void);
int  md5(char * sum, const char * m, int bytes);
void md5_format(char * output, const char * sum);
void md5_format_ex(char * output, const char * buf, int bytes);
int  md5_get_err_number(void);
void md5_set_err_number(int n);
 
#endif