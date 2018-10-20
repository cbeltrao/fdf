/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:13:28 by ayip              #+#    #+#             */
/*   Updated: 2017/09/20 15:46:14 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *big, const char *little)
{
	int		i;

	if (!*little)
		return ((char*)big);
	while (*big)
	{
		if (*big == *little)
		{
			i = 1;
			while (*(big + i) && *(big + i) == *(little + i))
				i++;
			if (*(little + i) == 0)
				return ((char*)big);
		}
		big++;
	}
	return ((char*)0);
}
