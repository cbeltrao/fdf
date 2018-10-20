/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 03:20:02 by ayip              #+#    #+#             */
/*   Updated: 2017/09/21 05:30:48 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numdigits(int n)
{
	int		i;

	i = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		isneg;
	long	val;
	char	*tmp;
	int		i;

	isneg = (n < 0 ? 1 : 0);
	val = (n < 0 ? 0 - (long)n : n);
	if (!(tmp = malloc(ft_numdigits(n) + isneg + 1)))
		return (NULL);
	i = 0;
	if (!val)
		tmp[i++] = '0';
	while (val > 0)
	{
		tmp[i] = val % 10 + '0';
		val /= 10;
		i++;
	}
	if (isneg)
		tmp[i++] = '-';
	tmp[i] = 0;
	return (ft_strrev(tmp));
}
