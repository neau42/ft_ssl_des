/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 16:49:16 by nboulaye          #+#    #+#             */
/*   Updated: 2018/12/02 09:44:08 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <inttypes.h>

int64_t		ft_atoi(const char *str);
int64_t		ft_atoh(char *str);
int64_t		ft_atoh_rpadd(char *str);
void		ft_bzero(void *s, size_t n);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_ishexdigit(int c);
int			ft_itoa_base_buffer(long double val, int base, char *buf);
void		*ft_memcpy(void *dst, const void *str, size_t n);
void		*ft_memset(void *b, int c, size_t len);
size_t		ft_strlen(const char *str);
char		*ft_strstr(const char *s1, const char *s2);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strtolower(char *str);
char		*ft_strncat(char *s1, const char *s2, size_t n);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_abs(int i);
void		ft_capitaliz(char *str);
char		*ft_strdup(const char *s1);
char		*ft_strnew(size_t size);
char		*ft_strncpy(char *dst, const char *src, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memalloc(size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		ft_strdel(char **as);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strjoin_free(char *s1, char *s2, int i);
char		*ft_strcat(char *s1, const char *s2);
char		**ft_strsplit(const char *s, char c);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strsplit_first(char *str, char c);
char		*ft_strrnchr(const char *s, int c, size_t max);
char		ft_strlast(char *str);

#endif
