/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:03:26 by asene             #+#    #+#             */
/*   Updated: 2024/12/04 12:03:45 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_coords(t_map *map, int x, int y)
{
	return (map->data[y / CELL_SIZE][x / CELL_SIZE] == '1');
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
	if (check_coords(game->map, x - 16, y - 16)
		|| check_coords(game->map, x + 16, y - 16)
		|| check_coords(game->map, x - 16, y + 16)
		|| check_coords(game->map, x + 16, y + 16))
		return (0);
	game->player.x = x;
	game->player.y = y;
	return (1);
}