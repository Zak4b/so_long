/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:37:01 by asene             #+#    #+#             */
/*   Updated: 2024/12/12 14:32:11 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_cell(t_game *g, int x, int y)
{
	t_img	*img;

	if (y < 0 || y >= g->map->height || x < 0 || x >= g->map->width)
		return ;
	if (g->map->data[y][x] == '1')
		img = g->wall;
	else
		img = g->floor;
	mlx_put_image_to_window(g->mlx, g->mlx_win, img->img,
		x * CELL_SIZE, y * CELL_SIZE);
	if (g->map->data[y][x] == 'C')
		put_image(g, g->item, x * CELL_SIZE + (CELL_SIZE - g->item->width) / 2,
			y * CELL_SIZE + (CELL_SIZE - g->item->height) / 2);
	else if (g->map->data[y][x] == 'E')
		put_image(g, g->exit[g->map->items == 0],
			g->map->exit.x * CELL_SIZE + (CELL_SIZE - g->exit[0]->width) / 2,
			g->map->exit.y * CELL_SIZE + (CELL_SIZE - g->exit[0]->height) / 2);
}
/*
void	render_arround(t_game *game, int x0, int y0)
{
	int	x;
	int	y;

	y = y0 - 1;
	while (y <= y0 + 1)
	{
		x = x0 - 1;
		while (x <= x0 + 1)
			render_cell(game, x++, y);
		y++;
	}
}
*/

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
	t_img	*img;

	if (e->dir != e->last_dir || e->mov != e->last_mov)
		e->anim_state = 0;
	e->last_dir = e->dir;
	e->last_mov = e->mov;
	if (e->type == PLAYER)
		img = game->img[e->mov][e->dir][e->anim_state++];
	else
		img = game->simg[e->dir][e->anim_state++];
	if (img == NULL)
		return (e->anim_state = 0, render_entity(game, e));
	put_image(game, img, e->x - 32, e->y - 32);
}

void	render_enemies(t_game *game)
{
	t_list		*enemies;

	enemies = game->enemies;
	while (enemies != NULL)
	{
		render_entity(game, enemies->content);
		enemies = enemies->next;
	}
}

void	render_move_count(t_game *game, unsigned int nb)
{
	int		i;
	int		x;
	int		y;

	x = CELL_SIZE * (game->map->width) - game->digits[0]->width * 1.5;
	y = CELL_SIZE * (game->map->height) - game->digits[0]->height * 1.5;
	i = 0;
	while (i++ < game->map->width)
		render_cell(game, i, game->map->height - 1);
	while (1)
	{
		put_image(game, game->digits[nb % 10], x, y);
		x -= 1.5 * game->digits[nb % 10]->width;
		nb /= 10;
		if (nb == 0)
			break ;
	}
}
