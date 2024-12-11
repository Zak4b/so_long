/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:35:22 by asene             #+#    #+#             */
/*   Updated: 2024/12/11 15:20:44 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_image(t_game *game, t_img *img)
{
	mlx_destroy_image(game->mlx, img->img);
	free(img);
}

void	clear_lst_img(t_game *game, t_list **lst)
{
	t_img	*i;

	if (lst == NULL || *lst == NULL)
		return ;
	if ((*lst)->next)
		clear_lst_img(game, &((*lst)->next));
	i = (*lst)->content;
	free_image(game, i);
	free(*lst);
	*lst = NULL;
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
