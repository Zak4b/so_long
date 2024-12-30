/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:53:44 by asene             #+#    #+#             */
/*   Updated: 2024/12/31 00:42:20 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static int	solve_map(t_map *map, t_point p, int *exit)
{
	if (p.x < 0 || p.x >= map->width || p.y < 0 || p.y >= map->height)
		return (0);
	if (map->data[p.y][p.x] == '1')
		return (0);
	else if (map->data[p.y][p.x] == 'C')
		map->items--;
	else if (map->data[p.y][p.x] == 'E')
		(*exit)--;
	map->data[p.y][p.x] = '1';
	solve_map(map, new_point(p.x - 1, p.y), exit);
	solve_map(map, new_point(p.x, p.y - 1), exit);
	solve_map(map, new_point(p.x + 1, p.y), exit);
	solve_map(map, new_point(p.x, p.y + 1), exit);
	return (1);
}

void	count_specials(t_map *map, int *entrance, int *exit)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->data[y][x])
		{
			if (map->data[y][x] == 'C')
				map->items++;
			else if (map->data[y][x] == 'E')
			{
				map->exit = new_point(x, y);
				(*exit)++;
			}
			else if (map->data[y][x] == 'P')
			{
				map->entrance = new_point(x, y);
				(*entrance)++;
			}
			x++;
		}
		y++;
	}
}

void	map_error_msg(char *msg)
{
	ft_fprintf(2, "Invalid map, %s\n", msg);
}

int	check_map(t_map *map)
{
	t_map	*map_dup;
	int		entrance;
	int		exit;
	int		items;

	entrance = 0;
	exit = 0;
	count_specials(map, &entrance, &exit);
	if (exit != 1 || entrance != 1 || map->items < 1)
	{
		if (map->items < 1)
			map_error_msg("not enough items");
		else
			map_error_msg("need at least 1 entrance and 1 exit");
		return (0);
	}
	map_dup = dup_map(map);
	solve_map(map_dup, map->entrance, &exit);
	items = map_dup->items;
	clear_map(map_dup);
	if (exit != 0 || items != 0)
		return (map_error_msg("can't solve map"), 0);
	return (1);
}
