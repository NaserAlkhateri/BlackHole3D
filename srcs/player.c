/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:45:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/10 16:27:24 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_dir_plane2(t_scene *s, char c)
{
	if (c == 'E')
	{
		s->dirx = 1.0;
		s->diry = 0.0;
		s->plx = 0.0;
		s->ply = 0.66;
	}
	if (c == 'W')
	{
		s->dirx = -1.0;
		s->diry = 0.0;
		s->plx = 0.0;
		s->ply = -0.66;
	}
}

static void	set_dir_plane(t_scene *s, char c)
{
	if (c == 'N')
	{
		s->dirx = 0.0;
		s->diry = -1.0;
		s->plx = 0.66;
		s->ply = 0.0;
	}
	if (c == 'S')
	{
		s->dirx = 0.0;
		s->diry = 1.0;
		s->plx = -0.66;
		s->ply = 0.0;
	}
	set_dir_plane2(s, c);
}

void	init_player_from_map(t_scene *s)
{
	int	y;
	int	x;

	y = 0;
	while (y < s->map_h)
	{
		x = 0;
		while (x < s->map_w)
		{
			if (s->map[y][x] == 'N' || s->map[y][x] == 'S'
				|| s->map[y][x] == 'E' || s->map[y][x] == 'W')
			{
				s->px = x + 0.5;
				s->py = y + 0.5;
				set_dir_plane(s, s->map[y][x]);
				s->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
