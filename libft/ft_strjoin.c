/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 23:28:59 by ayip              #+#    #+#             */
/*   Updated: 2017/09/21 00:23:05 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SNEMPTY (s1 ? s1 : s2)

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;

	if (s1 && s2)
	{
		if (!(tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
			return (NULL);
		ft_strcpy(tmp, s1);
		ft_strcat(tmp, s2);
		return (tmp);
	}
	else if (!s1 != !s2)
	{
		if (!(tmp = ft_strnew(ft_strlen(SNEMPTY))))
			return (NULL);
		ft_strcpy(tmp, SNEMPTY);
		return (tmp);
	}
	else
		return (NULL);
}
