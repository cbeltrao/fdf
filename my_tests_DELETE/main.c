/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 22:37:45 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/20 22:45:28 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char **tmp;
	int i = 0;

	tmp = (char **)malloc(sizeof(char *) * 3);
	while(i < 2)
	{
		tmp[i] = (char *)malloc(sizeof(char) * 3);
		tmp[i][0] = ('a' + i);
		tmp[i][1] = ('b' + i);
		tmp[i][2] = '\0';
		i++;
	}
	tmp[2] = NULL;
	
	while(*tmp)
		printf("%c\n", **tmp++);
	return (0);
}
