/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:31:59 by asene             #+#    #+#             */
/*   Updated: 2024/11/29 16:31:32 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int key_hook(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        close_window(game);
	else if (keycode == KEY_A)
	{
		game->player.x -= CELL_SIZE;
		game->player.dir = 0;
	}
	else if (keycode == KEY_W)
	{
		game->player.y -= CELL_SIZE;
		game->player.dir = 1;
	}
	else if (keycode == KEY_D)
	{
		game->player.x += CELL_SIZE;
		game->player.dir = 2;
	}
	else if (keycode == KEY_S)
	{
		game->player.y += CELL_SIZE;
		game->player.dir = 3;
	}
    return 0;
}
int close_window(t_game *game)
{
	int i;

	i = 0;
	while (i < game->map->height)
		free(game->map->data[i++]);
	free(game->map->data);
	free(game->map);
	//ft_lstclear(&(game->img), mlx_destroy_image);
    exit(EXIT_SUCCESS);
    return 0;
}