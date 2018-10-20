/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 00:23:57 by ayip              #+#    #+#             */
/*   Updated: 2017/09/21 00:48:37 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*tmp;
	int		start;
	int		end;

	if (!s)
		return (NULL);
	start = 0;
	while (ft_isspace(s[start]))
		start++;
	end = ft_strlen(s) - 1;
	while (ft_isspace(s[end]) && end >= start)
		end--;
	if (start > end)
		return (ft_strnew(0));
	if (!(tmp = ft_strnew(end - start + 1)))
		return (NULL);
	end = end - start + 1;
	while (end-- > 0)
		tmp[end] = s[start + end];
	return (tmp);
}
