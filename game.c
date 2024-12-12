/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:03:26 by asene             #+#    #+#             */
/*   Updated: 2024/12/12 14:51:18 by asene            ###   ########.fr       */
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

t_entity	*new_entity(t_type type, int x, int y)
{
	t_entity	*e;

	e = ft_calloc(1, sizeof(t_entity));
	e->type = type;
	e->x = x;
	e->y = y;
	e->mov = 0;
	e->last_mov = e->mov;
	e->dir = D_RIGHT;
	e->last_dir = e->dir;
	e->anim_state = 0;
	return (e);
}

int	move_entity(t_game *game, t_entity *e)
{
	const int	dx[] = {-MOVE_DISTANCE, 0, MOVE_DISTANCE, 0};
	const int	dy[] = {0, -MOVE_DISTANCE, 0, MOVE_DISTANCE};
	int			x;
	int			y;

	if (!e->mov)
		return (0);
	x = e->x + dx[e->dir];
	y = e->y + dy[e->dir];
	if (check_coords(game->map, x - 16, y - 16) == '1'
		|| check_coords(game->map, x + 16, y - 16) == '1'
		|| check_coords(game->map, x - 16, y + 16) == '1'
		|| check_coords(game->map, x + 16, y + 16) == '1')
		return (0);
	e->x = x;
	e->y = y;
	return (1);
}

int	pickup_item(t_game *game)
{
	int	x;
	int	y;

	if (check_coords(game->map, game->player->x, game->player->y) != 'C')
		return (0);
	x = game->player->x / CELL_SIZE;
	y = game->player->y / CELL_SIZE;
	game->map->data[y][x] = '0';
	game->map->items--;
	return (1);
}
