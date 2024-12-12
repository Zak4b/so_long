/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:35:22 by asene             #+#    #+#             */
/*   Updated: 2024/12/12 12:18:10 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_image(t_game *game, t_img *img)
{
	mlx_destroy_image(game->mlx, img->img);
	free(img);
}

void	clear_array_img(t_game *game, t_img **imgs)
{
	t_img	**arr;

	arr = imgs;
	while (*imgs)
	{
		free_image(game, *imgs);
		imgs++;
	}
	free(arr);
}
