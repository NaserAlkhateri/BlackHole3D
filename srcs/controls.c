/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:35:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/23 22:17:11 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	move_fb(t_mlx *m, double step)
{
	double	nx;
	double	ny;
	int		gx;
	int		gy;

	nx = m->scn->px + m->scn->dirx * step;
	ny = m->scn->py + m->scn->diry * step;
	gx = (int)nx;
	gy = (int)ny;
	if (gx >= 0 && gy >= 0 && gx < m->scn->map_w && gy < m->scn->map_h
		&& m->scn->map[gy][gx] != '1' && m->scn->map[gy][gx] != ' ')
	{
		m->scn->px = nx;
		m->scn->py = ny;
	}
	else
	{
		gx = (int)nx;
		gy = (int)m->scn->py;
		if (gx >= 0 && gy >= 0 && gx < m->scn->map_w && gy < m->scn->map_h
			&& m->scn->map[gy][gx] != '1' && m->scn->map[gy][gx] != ' ')
			m->scn->px = nx;
		gx = (int)m->scn->px;
		gy = (int)ny;
		if (gx >= 0 && gy >= 0 && gx < m->scn->map_w && gy < m->scn->map_h
			&& m->scn->map[gy][gx] != '1' && m->scn->map[gy][gx] != ' ')
			m->scn->py = ny;
	}
}

static void	strafe_lr(t_mlx *m, double step)
{
	double	nx;
	double	ny;
	int		gx;
	int		gy;

	nx = m->scn->px + m->scn->plx * step;
	ny = m->scn->py + m->scn->ply * step;
	gx = (int)nx;
	gy = (int)ny;
	if (gx >= 0 && gy >= 0 && gx < m->scn->map_w && gy < m->scn->map_h
		&& m->scn->map[gy][gx] != '1' && m->scn->map[gy][gx] != ' ')
	{
		m->scn->px = nx;
		m->scn->py = ny;
	}
	else
	{
		gx = (int)nx;
		gy = (int)m->scn->py;
		if (gx >= 0 && gy >= 0 && gx < m->scn->map_w && gy < m->scn->map_h
			&& m->scn->map[gy][gx] != '1' && m->scn->map[gy][gx] != ' ')
			m->scn->px = nx;
		gx = (int)m->scn->px;
		gy = (int)ny;
		if (gx >= 0 && gy >= 0 && gx < m->scn->map_w && gy < m->scn->map_h
			&& m->scn->map[gy][gx] != '1' && m->scn->map[gy][gx] != ' ')
			m->scn->py = ny;
	}
}


static void	rotate_view(t_mlx *m, double a)
{
	double oldx;
	double oldpx;

	oldx = m->scn->dirx;
	m->scn->dirx = m->scn->dirx * cos(a) - m->scn->diry * sin(a);
	m->scn->diry = oldx * sin(a) + m->scn->diry * cos(a);
	oldpx = m->scn->plx;
	m->scn->plx = m->scn->plx * cos(a) - m->scn->ply * sin(a);
	m->scn->ply = oldpx * sin(a) + m->scn->ply * cos(a);
}

int	handle_key(t_mlx *m, int key)
{
	double	move;
	double	rot;
	int		used;

	move = 0.10;
	rot = 0.05;
	used = 0;
	if (key == KEY_W_M || key == KEY_W_L)
		(move_fb(m, +move), used = 1);
	if (key == KEY_S_M || key == KEY_S_L)
		(move_fb(m, -move), used = 1);
	if (key == KEY_A_M || key == KEY_A_L)
		(strafe_lr(m, -move), used = 1);
	if (key == KEY_D_M || key == KEY_D_L)
		(strafe_lr(m, +move), used = 1);
	if (key == KEY_LEFT_M || key == KEY_LEFT_L)
		(rotate_view(m, -rot), used = 1);
	if (key == KEY_RIGHT_M || key == KEY_RIGHT_L)
		(rotate_view(m, +rot), used = 1);
	return (used);
}
