/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:45:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/30 14:50:51 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static const char	*check_top_bottom(t_scene *scn)
{
	int	x;

	x = 0;
	while (x < scn->map_w)
	{
		if (scn->map[0][x] != ' ' && scn->map[0][x] != '1')
			return ("Map not closed at top");
		if (scn->map[scn->map_h - 1][x] != ' ' &&
			scn->map[scn->map_h - 1][x] != '1')
			return ("Map not closed at bottom");
		x++;
	}
	return (NULL);
}

static const char	*check_left_right(t_scene *scn)
{
	int	y;

	y = 0;
	while (y < scn->map_h)
	{
		if (scn->map[y][0] != ' ' && scn->map[y][0] != '1')
			return ("Map not closed on left");
		if (scn->map[y][scn->map_w - 1] != ' ' &&
			scn->map[y][scn->map_w - 1] != '1')
			return ("Map not closed on right");
		y++;
	}
	return (NULL);
}

static const char	*check_interior(t_scene *scn)
{
	int		y;
	int		x;
	char	c;

	y = 1;
	while (y < scn->map_h - 1)
	{
		x = 1;
		while (x < scn->map_w - 1)
		{
			c = scn->map[y][x];
			if (c != ' ' && c != '1')
				if (scn->map[y - 1][x] == ' ' || scn->map[y + 1][x] == ' ' ||
					scn->map[y][x - 1] == ' ' || scn->map[y][x + 1] == ' ')
					return ("Map has interior hole");
			x++;
		}
		y++;
	}
	return (NULL);
}

const char	*check_walls_and_holes(t_scene *scn)
{
	const char	*err;

	err = check_top_bottom(scn);
	if (err)
		return (err);
	err = check_left_right(scn);
	if (err)
		return (err);
	return (check_interior(scn));
}

const char	*validate_map(t_scene *s)
{
	int			y;
	int			pc;
	const char	*err;

	if (!s || !s->map)
		return ("Map is not present");
	pc = 0;
	y = -1;
	while (++y < s->map_h)
	{
		err = validate_row(s, y, &pc);
		if (err)
			return (err);
	}
	if (pc == 0)
		return ("No player start position");
	if (pc > 1)
		return ("Multiple player start positions");
	return (check_walls_and_holes(s));
}
