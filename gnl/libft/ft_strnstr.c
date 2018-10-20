/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:13:19 by ayip              #+#    #+#             */
/*   Updated: 2017/09/20 15:59:43 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;

	if (!*little)
		return ((char*)big);
	while (*big && len-- > 0)
	{
		if (*big == *little)
		{
			i = 1;
			while (*(big + i) && *(big + i) == *(little + i))
				i++;
			if (*(little + i) == 0 && (int)len >= i - 1)
				return ((char*)big);
		}
		big++;
	}
	return ((char*)0);
}
