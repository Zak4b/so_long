/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:08:17 by asene             #+#    #+#             */
/*   Updated: 2024/12/16 14:53:51 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	distance(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;

	dx = abs(x1 - x2);
	dy = abs(y1 - y2);
	if (dx > dy)
		return (dx);
	else
		return (dy);
}

int	distance_to_exit(t_game *game)
{
	return (distance((game->map->exit.x +.5) * CELL_SIZE,
			(game->map->exit.y +.5) * CELL_SIZE,
			game->player->x, game->player->y));
}

int	distance_entity(t_entity *e1, t_entity *e2)
{
	return (distance(e1->x, e1->y, e2->x, e2->y));
}
