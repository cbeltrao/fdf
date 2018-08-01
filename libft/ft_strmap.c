/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:54:05 by ayip              #+#    #+#             */
/*   Updated: 2017/09/20 21:53:05 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*tmp;
	char	*ptr;

	if (s)
	{
		if (!(tmp = ft_strnew(ft_strlen(s))))
			return (NULL);
		ptr = tmp;
		while (*s)
			*ptr++ = f(*s++);
		return (tmp);
	}
	else
		return (ft_strnew(0));
}
