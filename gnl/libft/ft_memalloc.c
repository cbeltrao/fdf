/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:07:21 by ayip              #+#    #+#             */
/*   Updated: 2017/09/20 16:14:57 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_memalloc(size_t size)
{
	char	*tmp;
	int		i;

	if (!(tmp = malloc(size)))
		return (NULL);
	i = 0;
	while (i < (int)size)
		*(tmp + i++) = 0;
	return ((void*)tmp);
}
