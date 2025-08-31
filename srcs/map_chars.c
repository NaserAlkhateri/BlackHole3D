/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 06:10:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/30 14:05:57 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_map_char(char c)
{
	if (c == ' ' || c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

const char	*validate_row(t_scene *s, int y, int *pc)
{
	int		x;
	char	c;

	x = -1;
	while (++x < s->map_w)
	{
		c = s->map[y][x];
		if (!is_map_char(c))
			return ("Invalid character in map");
		if (is_player_char(c))
			(*pc)++;
	}
	return (NULL);
}
