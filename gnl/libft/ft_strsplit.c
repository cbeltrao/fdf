/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 00:49:21 by ayip              #+#    #+#             */
/*   Updated: 2017/09/23 16:46:44 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_safestrlen(const char *s)
{
	int		len;

	len = 0;
	if (s)
		while (s[len])
			len++;
	return (len);
}

static char		**empty_strarray(void)
{
	char	**tmp;

	if (!(tmp = malloc(sizeof(char*))))
		return (NULL);
	*tmp = NULL;
	return (tmp);
}

static char		**filled_strarray(char const *s, int *pos, int numpos)
{
	char	**tmp;
	int		i;
	int		j;

	if (!(tmp = malloc(sizeof(char*) * (numpos / 2 + 1))))
		return (NULL);
	tmp[numpos / 2] = NULL;
	i = 0;
	while (i < numpos / 2)
	{
		if (!(tmp[i] = ft_strnew(pos[i * 2 + 1] - pos[i * 2] + 1)))
			return (NULL);
		j = 0;
		while (j < pos[i * 2 + 1] - pos[i * 2] + 1)
		{
			tmp[i][j] = s[pos[i * 2] + j];
			j++;
		}
		i++;
	}
	return (tmp);
}

char			**ft_strsplit(char const *s, char c)
{
	int		pos[ft_safestrlen(s) + 1];
	int		i;
	int		numpos;

	if (sizeof(pos) == sizeof(int))
		return (empty_strarray());
	i = 0;
	numpos = 0;
	if (i == 0 && s[0] != c)
		pos[numpos++] = 0;
	while (s[i])
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			pos[numpos++] = i++;
		else if (s[i] == c && s[i + 1] != c && s[i + 1] != 0)
			pos[numpos++] = ++i;
		else
			i++;
	if (numpos == 0)
		return (empty_strarray());
	return (filled_strarray(s, pos, numpos));
}
