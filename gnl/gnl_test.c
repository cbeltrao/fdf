/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeltrao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 15:09:15 by cbeltrao          #+#    #+#             */
/*   Updated: 2018/09/26 19:19:30 by cbeltrao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int		ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while(*(arr + i))
		i++;
	return --i;
}

int		**grid_add_line(int **map_grid, char *line, int i,int line_len)
{
    char    **tmp;
    int     j;

    line_len = ft_arrlen(ft_strsplit(line, ' '));
    j = 0;
    if(!line || !map_grid)
        return (NULL);
    tmp = ft_strsplit(line, ' ');
    *(map_grid + i) = (int *)malloc((sizeof (int)) * line_len);
    while(*tmp)
    {
        map_grid[i][j] = ft_atoi(*tmp++);
        j++;
    }
    /* Print test */

    return (map_grid);

}

int     **read_map(char *map_name)
{
    int     fd;
    int     line_nbr;
    char    *line;
    int     **map_grid;
    int     len;

    fd = open(map_name, O_RDONLY);
    line_nbr = 0;
    while (get_next_line(fd, &line))
        line_nbr++;
    close(fd);
    map_grid = (int **)malloc((sizeof (int*)) * line_nbr);
    fd = open(map_name, O_RDONLY);
    line_nbr = 0;
    while (get_next_line(fd, &line))
    {
        map_grid = grid_add_line(map_grid, line, line_nbr, ft_arrlen(ft_strsplit(line, ' ')));
        line_nbr++;
    }
	len = ft_arrlen(ft_strsplit(line, ' '));
	--line_nbr;
    close(fd);
    fd = 0;
    while(line_nbr >= 0)
    {
        while(fd < len)
        {
            printf("%d,", map_grid[line_nbr][fd]);
            fd++;
        }
        printf("\n");
        line_nbr--;
    }
	return map_grid;
}

int main(int argc, char **argv)
{
	(void)argc;
	read_map(argv[1]);	
	return (0);
}
