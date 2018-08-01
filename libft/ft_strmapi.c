/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 21:54:12 by ayip              #+#    #+#             */
/*   Updated: 2017/09/20 22:16:23 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*tmp;
	unsigned int	u;

	u = 0;
	if (s)
	{
		if (!(tmp = ft_strnew(ft_strlen(s))))
			return (NULL);
		while (s[u])
		{
			tmp[u] = f(u, s[u]);
			u++;
		}
		return (tmp);
	}
	else
		return (ft_strnew(0));
}
