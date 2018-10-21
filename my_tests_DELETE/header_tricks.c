/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_tricks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:52:42 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/10/21 18:02:29 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define DEPTH_OF(x) (sizeof(x)/sizeof(int *))

int print_depth(int **map)
{
	printf("%lu", DEPTH_OF(map));
	printf("sizeof manual:%lu", sizeof(map[0])/sizeof(map[0][0]));
	return (0);
}

int main(void)
{
	int **map;
	int i = 0;
	int j = 0;
	map = (int **)malloc(sizeof(int *) * 4);
	map[0] = (int *)malloc(sizeof(int) * 4);
	map[1] = (int *)malloc(sizeof(int) * 4);
	map[2] = (int *)malloc(sizeof(int) * 4);
	map[3] = (int *)malloc(sizeof(int) * 4);
	while(i < 4)
	{
		j = 0;
		while(j < 4)
		{
			map[i][j] = 1;
			printf("##%d ", map[i][j]);
			j++;
		}
		i++;
	}
	print_depth(map);
	return (0);
}
