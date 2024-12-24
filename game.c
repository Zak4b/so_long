/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:03:26 by asene             #+#    #+#             */
/*   Updated: 2024/12/24 15:05:22 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_entity	*new_entity(t_type type, int x, int y)
{
	t_entity	*e;

	e = ft_calloc(1, sizeof(t_entity));
	e->type = type;
	e->x = x;
	e->y = y;
	e->mov = IDLE;
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

	if (e->mov != WALK)
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

void	move_entities(t_game *game)
{
	t_list		*lst;
	t_entity	*e;

	lst = game->entities;
	while (lst != NULL)
	{
		e = lst->content;
		if (e->mov != DEAD)
		{
			if (move_entity(game, e))
			{
				if (e == game->player)
					game->move_count++;
			}
			else if (e->type == MONSTER)
			{
				if (e->dir == D_RIGHT)
					e->dir = D_LEFT;
				else
					e->dir = D_RIGHT;
			}
		}
		lst = lst->next;
	}
	check_collide(game);
}

void	check_collide(t_game *game)
{
	t_list		*lst;
	t_entity	*e;
	int			d;

	lst = game->entities;
	while (lst != NULL)
	{
		e = lst->content;
		if (e->type != PLAYER)
		{
			d = distance_entity(game->player, e);
			if (game->player->mov == ATTACK)
				if (d <= 48)
					e->mov = DEAD;
			if (e->mov != DEAD && d <= 24)
				return (game->player->mov = DEAD, (void)0);
		}
		lst = lst->next;
	}
}

int	pickup_item(t_game *game)
{
	int	cell_x;
	int	cell_y;
	int	x;
	int	y;

	cell_x = game->player->x / CELL_SIZE;
	cell_y = game->player->y / CELL_SIZE;
	x = (cell_x +.5) * CELL_SIZE;
	y = (cell_y +.5) * CELL_SIZE;
	if (distance(game->player->x, game->player->y, x, y) > 16
		|| game->map->data[cell_y][cell_x] != 'C')
		return (0);
	game->map->data[cell_y][cell_x] = '0';
	game->map->items--;
	return (1);
}
