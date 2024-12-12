/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:01:28 by asene             #+#    #+#             */
/*   Updated: 2024/12/12 18:00:51 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->entrance = new_point(-1, -1);
	map->exit = new_point(-1, -1);
	map->items = 0;
	map->width = -1;
	map->height = 0;
	map->data = NULL;
	return (map);
}

void	clear_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
		free(map->data[i++]);
	free(map->data);
	free(map);
}

t_map	*dup_map(t_map *map)
{
	int		i;
	t_map	*dup;

	dup = init_map();
	dup->entrance = map->entrance;
	dup->exit = map->exit;
	dup->items = map->items;
	dup->height = map->height;
	dup->width = map->width;
	dup->data = malloc(sizeof(char *) * dup->height);
	i = 0;
	while (i < dup->height)
	{
		dup->data[i] = ft_strdup(map->data[i]);
		i++;
	}
	return (dup);
}

t_point	new_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

char	check_coords(t_map *map, int x, int y)
{
	t_point	p;

	p = new_point(x / CELL_SIZE, y / CELL_SIZE);
	if (p.y < 0 || p.y >= map->height || p.x < 0 || p.x >= map->width)
		return (0);
	return (map->data[p.y][p.x]);
}
