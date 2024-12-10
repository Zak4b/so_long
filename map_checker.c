/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:53:44 by asene             #+#    #+#             */
/*   Updated: 2024/12/10 10:32:30 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	solve_map(t_map *map, int x, int y)
{
	
}

void	find_entrance(t_map *map)
{
	int	x;
	int	y;
	int item;
	int	exit;
	int	entrance;

	item = 0;
	exit = 0;
	entrance = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->data[y][x])
		{
			if (map->data[y][x] == 'C')
				item++;
			else if (map->data[y][x] == 'E')
				exit++;
			else if (map->data[y][x] == 'P')
				entrance++;
			x++;
		}
		map->data[y];
		y++;
	}
}

int	check_map(t_map *map)
{
	int		i;
	t_map	map_dup;

	map_dup.height = map->height;
	map_dup.width = map->width;
	map_dup.data = malloc(sizeof(char *) * map_dup.height);
	i = 0;
	while (i < map_dup.height)
	{
		map_dup.data[i] = ft_strdup(map->data[i]);
		i++;
	}
	solve_map(&map_dup, 0, 0);
}
