/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:01:28 by asene             #+#    #+#             */
/*   Updated: 2024/12/10 13:10:47 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->width = -1;
	map->height = 0;
	map->data = NULL;
	return (map);
}
void	clear_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->height)
		free(map->data[i++]);
	free(map->data);
	free(map);
}