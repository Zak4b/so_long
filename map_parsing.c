/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:57:27 by asene             #+#    #+#             */
/*   Updated: 2024/11/29 16:06:18 by asene            ###   ########.fr       */
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
	map->data = NULL;
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

t_list	*map_list(int fd, int *width, int *height)
{
	t_list	*lst;
	char	*line;

	lst = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		sanitize_line(&line);
		if (*width == -1)
		{
			*width = ft_strlen(line);
			if (*width < 3)
				return (free(line), exit(EXIT_FAILURE), NULL);
		}
		else if ((size_t)*width != ft_strlen(line) || !line_is_valid(line))
			return (free(line), ft_lstclear(&lst, free), NULL);
		ft_lstadd_back(&lst, ft_lstnew(line));
		(*height)++;
	}
	return (lst);
}

t_map	*parse_map(int fd)
{
	int		i;
	t_list	*lst_start;
	t_list	*lst;
	t_map	*map;

	map = init_map();
	lst_start = map_list(fd, &(map->width), &(map->height));
	lst = lst_start;
	i = 0;
	map->data = ft_calloc(map->height + 1, sizeof(char *));
	if (map->data == NULL)
		return (ft_lstclear(&lst_start, free), NULL);
	while (i < map->height)
	{
		map->data[i++] = lst->content;
		lst = lst->next;
	}
	ft_lstclear(&lst_start, NULL);
	return (map);
}
