/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:23:04 by ayip              #+#    #+#             */
/*   Updated: 2017/09/20 16:26:36 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strnew(size_t size)
{
	char	*tmp;
	int		i;

	if (!(tmp = malloc(size + 1)))
		return (NULL);
	i = 0;
	while (i < (int)size + 1)
		*(tmp + i++) = 0;
	return (tmp);
}
