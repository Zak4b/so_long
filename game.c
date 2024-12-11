/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:03:26 by asene             #+#    #+#             */
/*   Updated: 2024/12/11 14:26:25 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	check_coords(t_map *map, int x, int y)
{
	t_point	p;

	p = new_point(x / CELL_SIZE, y / CELL_SIZE);
	if (p.y < 0 || p.y >= map->height || p.x < 0 || p.x >= map->width)
		return (0);
	return (map->data[p.y][p.x]);
}

int	move_player(t_game *game)
{
	const int	dx[] = {-MOVE_DISTANCE, 0, MOVE_DISTANCE, 0};
	const int	dy[] = {0, -MOVE_DISTANCE, 0, MOVE_DISTANCE};
	int			x;
	int			y;

	if (!game->player.mov)
		return (0);
	x = game->player.x + dx[game->player.dir];
	y = game->player.y + dy[game->player.dir];
	if (check_coords(game->map, x - 16, y - 16) == '1'
		|| check_coords(game->map, x + 16, y - 16) == '1'
		|| check_coords(game->map, x - 16, y + 16) == '1'
		|| check_coords(game->map, x + 16, y + 16) == '1')
		return (0);
	game->player.x = x;
	game->player.y = y;
	return (1);
}

int	pickup_item(t_game *game)
{
	int	x;
	int	y;

	if (check_coords(game->map, game->player.x, game->player.y) != 'C')
		return (0);
	x = game->player.x / CELL_SIZE;
	y = game->player.y / CELL_SIZE;
	game->map->data[y][x] = '0';
	game->map->items--;
	return (1);
}
