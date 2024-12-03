/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:31:59 by asene             #+#    #+#             */
/*   Updated: 2024/12/03 10:46:03 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_A)
	{
		game->player.x -= CELL_SIZE;
		game->player.dir = D_LEFT;
	}
	else if (keycode == KEY_W)
	{
		game->player.y -= CELL_SIZE;
		game->player.dir = D_UP;
	}
	else if (keycode == KEY_D)
	{
		game->player.x += CELL_SIZE;
		game->player.dir = D_RIGHT;
	}
	else if (keycode == KEY_S)
	{
		game->player.y += CELL_SIZE;
		game->player.dir = D_DOWN;
	}
	return (0);
}

void	clear_lst_img(t_game *game, t_list **lst)
{
	t_img	*i;

	if (lst == NULL || *lst == NULL)
		return ;
	if ((*lst)->next)
		clear_lst_img(game, &((*lst)->next));
	i = (*lst)->content;
	mlx_destroy_image(game->mlx, i->img);
	free(i);
	free(*lst);
	*lst = NULL;
}

int	close_window(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->height)
		free(game->map->data[i++]);
	free(game->map->data);
	free(game->map);
	clear_lst_img(game, &(game->img[0]));
	clear_lst_img(game, &(game->img[1]));
	clear_lst_img(game, &(game->img[2]));
	clear_lst_img(game, &(game->img[3]));
	mlx_destroy_image(game->mlx, game->floor_img->img);
	free(game->floor_img);
	mlx_destroy_image(game->mlx, game->wall_img->img);
	free(game->wall_img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}
