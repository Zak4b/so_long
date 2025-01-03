/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:37:01 by asene             #+#    #+#             */
/*   Updated: 2024/12/25 23:02:13 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	render_cell(t_game *g, int x, int y)
{
	t_img	*img;

	if (y < 0 || y >= g->map->height || x < 0 || x >= g->map->width)
		return ;
	if (g->map->data[y][x] == '1')
		img = g->wall;
	else
		img = g->floor;
	put_image(g->buffer[0], img, x * CELL_SIZE, y * CELL_SIZE);
	if (g->map->data[y][x] == 'C')
		put_image(g->buffer[0], g->item,
			x * CELL_SIZE + (CELL_SIZE - g->item->width) / 2,
			y * CELL_SIZE + (CELL_SIZE - g->item->height) / 2);
	else if (g->map->data[y][x] == 'E')
		put_image(g->buffer[0], g->exit[g->map->items == 0],
			g->map->exit.x * CELL_SIZE + (CELL_SIZE - g->exit[0]->width) / 2,
			g->map->exit.y * CELL_SIZE + (CELL_SIZE - g->exit[0]->height) / 2);
}

void	print_map(t_game *game)
{
	int		y;
	int		x;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
			render_cell(game, x++, y);
		y++;
	}
}

void	render_entity(t_game *game, t_entity *e)
{
	t_img	**img_array;
	int		d;

	if (e->dir != e->last_dir || e->mov != e->last_mov)
		e->anim_state = 0;
	e->last_dir = e->dir;
	e->last_mov = e->mov;
	d = e->dir;
	if (e->mov == DEAD)
		d = 0;
	img_array = game->img[e->type][e->mov][d];
	if (img_array[e->anim_state] == NULL)
	{
		if (e->mov == ATTACK)
			e->mov = IDLE;
		return (e->anim_state = 0, render_entity(game, e));
	}
	put_image(game->buffer[1], img_array[e->anim_state], e->x - 32, e->y - 32);
	if (e->mov == DEAD && img_array[e->anim_state + 1] == NULL)
		return ;
	e->anim_state++;
}

void	render_entities(t_game *game)
{
	t_list		*entities;

	entities = game->entities;
	while (entities != NULL)
	{
		render_entity(game, entities->content);
		entities = entities->next;
	}
}

void	render_move_count(t_game *game, unsigned int nb)
{
	int		x;
	int		y;

	x = CELL_SIZE * (game->map->width) - game->digits[0]->width * 1.5;
	y = CELL_SIZE * (game->map->height) - game->digits[0]->height * 1.5;
	while (1)
	{
		put_image(game->buffer[1], game->digits[nb % 10], x, y);
		x -= 1.5 * game->digits[nb % 10]->width;
		nb /= 10;
		if (nb == 0)
			break ;
	}
}
