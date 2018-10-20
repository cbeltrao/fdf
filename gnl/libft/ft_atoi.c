/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:56:00 by ayip              #+#    #+#             */
/*   Updated: 2017/09/18 18:54:44 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		digit;
	int		value;
	int		isneg;
	int		len;

	value = 0;
	while (ft_isspace(*str))
		str++;
	isneg = (*str == '-');
	if (*str == '+' || *str == '-')
		str++;
	len = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str++ - '0';
		value *= 10;
		value += digit;
		if (len++ > 18)
			return (isneg ? 0 : -1);
	}
	return (isneg ? 0 - value : value);
}
