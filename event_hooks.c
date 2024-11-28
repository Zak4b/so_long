/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:31:59 by asene             #+#    #+#             */
/*   Updated: 2024/11/28 16:07:46 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//int	mlx_draw_square(t_game *game, int x, int y);
int key_hook(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        close_window(game);
	else if (keycode == KEY_W)
		game->player.y -= CELL_SIZE;
	else if (keycode == KEY_A)
		game->player.x -= CELL_SIZE;
	else if (keycode == KEY_S)
		game->player.y += CELL_SIZE;
	else if (keycode == KEY_D)
		game->player.x += CELL_SIZE;
	// mlx_draw_square(game, game->player.x, game->player.y);
	// mlx_put_image_to_window(game->mlx, game->mlx_win, img.img, game->player.x, game->player.y);
    return 0;
}
int close_window(t_game *game)
{
	ft_lstclear(&(game->map->map_data), free);
	free(game->map);
    exit(EXIT_SUCCESS);
    return 0;
}