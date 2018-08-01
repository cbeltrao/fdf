/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 23:22:03 by ayip              #+#    #+#             */
/*   Updated: 2017/09/19 23:35:34 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	u1;
	unsigned char	u2;

	while (n-- > 0)
	{
		u1 = *(unsigned char*)s1++;
		u2 = *(unsigned char*)s2++;
		if (u1 != u2)
			return (u1 - u2);
	}
	return (0);
}
