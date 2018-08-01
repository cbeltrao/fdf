/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 18:55:25 by ayip              #+#    #+#             */
/*   Updated: 2017/11/07 01:36:48 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memrealloc(void *ptr, size_t size)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(tmp = malloc(size)))
		return (NULL);
	while (((char*)ptr)[i])
	{
		tmp[i] = ((char*)ptr)[i];
		i++;
	}
	while (i < size)
		tmp[i++] = 0;
	free(ptr);
	return (tmp);
}
