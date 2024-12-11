/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:37:01 by asene             #+#    #+#             */
/*   Updated: 2024/12/11 13:59:49 by asene            ###   ########.fr       */
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

void	render_player(t_game *game, int *t)
{
	int		i;
	t_list	*img;

	i = 0;
	img = game->img[game->player.mov][game->player.dir];
	while (i++ < *t)
		img = img->next;
	*t = (*t + 1) % 6;
	put_image(game, img->content, game->player.x - 32, game->player.y - 32);
}
