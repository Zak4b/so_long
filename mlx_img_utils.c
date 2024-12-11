/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:35:22 by asene             #+#    #+#             */
/*   Updated: 2024/12/11 15:08:11 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*build_path(char const *s1, char const *s2, int j)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		new_str[i++] = *(s1++);
	new_str[i++] = j + '0';
	while (*s2)
		new_str[i++] = *(s2++);
	new_str[i] = '\0';
	return (new_str);
}

t_img	*load_img(t_game *game, char *path)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	img->img = mlx_xpm_file_to_image(game->mlx, path,
			&(img->width), &(img->height));
	if (img->img != NULL)
		img->addr = mlx_get_data_addr(img->img, &(img->bpp),
				&(img->line_length), &(img->endian));
	return (img);
}

t_list	*load_sprites(t_game *game, char *path, unsigned int count)
{
	unsigned int	i;
	char			*full_path;
	t_list			*lst;

	lst = NULL;
	i = 0;
	while (i < count)
	{
		full_path = build_path(path, ".xpm", i);
		ft_lstadd_back(&lst, ft_lstnew(load_img(game, full_path)));
		free(full_path);
		i++;
	}
	return (lst);
}

t_img	**load_sprites_array(t_game *game, char *path, unsigned int count)
{
	unsigned int	i;
	char			*full_path;
	t_img			**imgs;

	imgs = ft_calloc(count + 1, sizeof(t_img *));
	i = 0;
	while (i < count)
	{
		full_path = build_path(path, ".xpm", i);
		imgs[i] = load_img(game, full_path);
		free(full_path);
		i++;
	}
	imgs[i] = NULL;
	return (imgs);
}

void	put_image(t_game *game, t_img *img, int x0, int y0)
{
	int	x;
	int	y;
	int	*img_data;
	int	color;

	img_data = (int *)img->addr;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = img_data[y * (img->line_length / 4) + x];
			if ((color >> 24 & 0xFF) == 0)
				mlx_pixel_put(game->mlx, game->mlx_win, x + x0, y + y0, color);
			x++;
		}
		y++;
	}
}
