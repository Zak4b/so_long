/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:35:22 by asene             #+#    #+#             */
/*   Updated: 2024/11/28 13:58:57 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
int	mlx_draw_line(int x1, int y1, int x2, int y2)
{
	
}
*/

int	mlx_draw_square(t_game *game, int x, int y)
{
	int xbase = x;
	int ybase = y;
    while (x < xbase + CELL_SIZE)
    {
        while(y < ybase + CELL_SIZE)
        {
			mlx_pixel_put(game->mlx, game->mlx_win, x, y, 0xFFFF0000);
        	y++;
        }
    	y = ybase;
    	x++;
    }
	return 0;
}
