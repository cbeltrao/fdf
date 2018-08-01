/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 19:12:35 by ayip              #+#    #+#             */
/*   Updated: 2017/09/19 23:08:35 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (d == s || len <= 0)
		return (dst);
	if (d < s)
	{
		while (len-- > 0)
			*d++ = *s++;
	}
	else
	{
		while (len-- > 0)
			*(d + len) = *(s + len);
	}
	return (dst);
}
