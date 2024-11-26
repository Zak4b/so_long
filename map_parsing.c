/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:57:27 by asene             #+#    #+#             */
/*   Updated: 2024/11/26 14:23:51 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map *init_map(void)
{
	t_map *map;

	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->width = -1;
	map->height = 0;
	map->map_data = NULL;
	return (map);
}

int	line_is_valid(const char *line)
{
	if (*line != '1')
		return (0);
	while (*line && ft_strchr("01CEP", *line))
		line++;
	return (*line == '\0');
}

void	sanitize_line(char **line)
{
	char	*n;

	n = ft_strchr(*line, '\n');
	if (n != NULL)
		*n = '\0';
}

t_map	*parse_map(int fd)
{
	t_map	*map;
	char	*line;

	map = init_map();
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		sanitize_line(&line);
		if (map->width == -1)
		{
			map->width = ft_strlen(line);
			if (map->width < 3)
				return (free(line), exit(EXIT_FAILURE), NULL);
		}
		else if ((size_t)map->width != ft_strlen(line) || !line_is_valid(line))
			return (free(line), ft_fprintf(2, "Invalid map\n"), NULL);
		ft_lstadd_back(&map->map_data, ft_lstnew(line));
		map->height++;
	}
	return (map);
}
