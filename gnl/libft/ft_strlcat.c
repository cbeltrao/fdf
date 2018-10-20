/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:06:11 by ayip              #+#    #+#             */
/*   Updated: 2017/09/23 23:56:31 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	char	*tmp;
	int		i;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	tmp = dst;
	while (*tmp)
		tmp++;
	i = 0;
	while (i++ < (int)size - (int)dstlen - 1)
		*tmp++ = *src++;
	*tmp = 0;
	return (size > dstlen ? srclen + dstlen : srclen + size);
}
