/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:45:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/10 16:27:30 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_img	*pick_tex(t_mlx *m, int side, double rx, double ry)
{
	if (side == 0 && rx > 0.0)
		return (&m->we);
	if (side == 0 && rx < 0.0)
		return (&m->ea);
	if (side == 1 && ry > 0.0)
		return (&m->no);
	return (&m->so);
}

static void	draw_column(t_mlx *m, int x, int y0, int y1, double wallx, t_img *tex)
{
	int		y;
	int		line_h;
	int		ty;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		col;

	line_h = y1 - y0 + 1;
	tex_x = (int)(wallx * (double)tex->w);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->w)
		tex_x = tex->w - 1;
	step = (double)tex->h / (double)line_h;
	tex_pos = 0.0;
	y = y0;
	while (y <= y1)
	{
		ty = (int)tex_pos;
		if (ty < 0)
			ty = 0;
		if (ty >= tex->h)
			ty = tex->h - 1;
		col = *(int *)(tex->addr + ty * tex->line_len + tex_x * (tex->bpp / 8));
		put_pixel(&m->img, x, y, col);
		tex_pos += step;
		y++;
	}
}

void	raycast_render(t_mlx *m)
{
	int		x;
	double	cx;
	double	rx;
	double	ry;
	double	ddx;
	double	ddy;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		side;
	double	sdistx;
	double	sdisty;
	double	pdist;
	int		hh;
	int		y0;
	int		y1;
	double	wallx;
	t_img	*tex;

	x = 0;
	while (x < WIN_W)
	{
		cx = 2.0 * x / (double)WIN_W - 1.0;
		rx = m->scn->dirx + m->scn->plx * cx;
		ry = m->scn->diry + m->scn->ply * cx;
		ddx = fabs(1.0 / (rx == 0.0 ? 1e-8 : rx));
		ddy = fabs(1.0 / (ry == 0.0 ? 1e-8 : ry));
		mapx = (int)m->scn->px;
		mapy = (int)m->scn->py;
		if (rx < 0.0)
		{
			stepx = -1;
			sdistx = (m->scn->px - mapx) * ddx;
		}
		else
		{
			stepx = 1;
			sdistx = (mapx + 1.0 - m->scn->px) * ddx;
		}
		if (ry < 0.0)
		{
			stepy = -1;
			sdisty = (m->scn->py - mapy) * ddy;
		}
		else
		{
			stepy = 1;
			sdisty = (mapy + 1.0 - m->scn->py) * ddy;
		}
		side = -1;
		while (side == -1)
		{
			if (sdistx < sdisty)
			{
				sdistx += ddx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sdisty += ddy;
				mapy += stepy;
				side = 1;
			}
			if (mapx < 0 || mapy < 0 || mapx >= m->scn->map_w || mapy >= m->scn->map_h)
				break ;
			if (m->scn->map[mapy][mapx] == '1')
				break ;
			side = -1;
		}
		if (side == 0)
			pdist = (mapx - m->scn->px + (1 - stepx) / 2.0) / (rx == 0.0 ? 1e-8 : rx);
		else
			pdist = (mapy - m->scn->py + (1 - stepy) / 2.0) / (ry == 0.0 ? 1e-8 : ry);
		hh = (int)(WIN_H / (pdist <= 1e-6 ? 1e-6 : pdist));
		y0 = -hh / 2 + WIN_H / 2;
		if (y0 < 0)
			y0 = 0;
		y1 = hh / 2 + WIN_H / 2;
		if (y1 >= WIN_H)
			y1 = WIN_H - 1;
		if (side == 0)
			wallx = m->scn->py + pdist * ry;
		else
			wallx = m->scn->px + pdist * rx;
		wallx -= floor(wallx);
		tex = pick_tex(m, side, rx, ry);
		draw_column(m, x, y0, y1, wallx, tex);
		x++;
	}
}
