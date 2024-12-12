/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:03:26 by asene             #+#    #+#             */
/*   Updated: 2024/12/12 18:00:30 by asene            ###   ########.fr       */
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

void	move_enemies(t_game *game)
{
	t_list		*lst;
	t_entity	*e;

	lst = game->enemies;
	while (lst != NULL)
	{
		e = lst->content;
		if (e->mov != DEAD && move_entity(game, e) == 0)
		{
			if (e->dir == D_RIGHT)
				e->dir = D_LEFT;
			else
				e->dir = D_RIGHT;
		}
		lst = lst->next;
	}
}

void	check_collide(t_game *game)
{
	t_list		*lst;
	t_entity	*e;
	int			dx;
	int			dy;

	lst = game->enemies;
	while (lst != NULL)
	{
		e = lst->content;
		dx = game->player->x - e->x;
		dy = game->player->y - e->y;
		if (game->player->mov == ATTACK)
		{
			if (dx <= 48 && dx >= -48 && dy <= 48 && dy >= -48)
				e->mov = DEAD;
		}
		if (e->mov != DEAD && dx <= 24 && dx >= -24 && dy <= 24 && dy >= -24)
		{
			game->player->mov = DEAD;
			return ;
		}
		lst = lst->next;
	}
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
