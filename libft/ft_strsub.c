/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:58:11 by ayip              #+#    #+#             */
/*   Updated: 2017/09/20 23:25:40 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tmp;

	if (s)
	{
		if (!(tmp = ft_strnew(len)))
			return (NULL);
		while (len-- > 0)
			*(tmp + len) = *(s + start + len);
		return (tmp);
	}
	return (NULL);
}
