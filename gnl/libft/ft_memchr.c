/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 23:13:44 by ayip              #+#    #+#             */
/*   Updated: 2017/09/20 15:22:41 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*tmp;

	tmp = s;
	while (n-- > 0)
	{
		if (*tmp++ == (unsigned char)c)
			return ((void*)s);
		s++;
	}
	return ((void*)NULL);
}
