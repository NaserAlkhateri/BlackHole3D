/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:45:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/10 16:27:30 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_column(t_mlx *m, t_colargs *a)
{
	t_draw	d;

	d.line_h = a->y1 - a->y0 + 1;
	d.tex_x = (int)(a->wallx * (double)a->tex->w);
	d.tex_x = clampi(d.tex_x, 0, a->tex->w - 1);
	d.step = (double)a->tex->h / (double)d.line_h;
	d.tex_pos = 0.0;
	d.y = a->y0;
	while (d.y <= a->y1)
	{
		d.ty = clampi((int)d.tex_pos, 0, a->tex->h - 1);
		d.col = sample_tex_color(a->tex, d.tex_x, d.ty);
		put_pixel(&m->img, a->x, d.y, d.col);
		d.tex_pos += d.step;
		d.y++;
	}
}

void	ray_init(t_mlx *m, int x, t_ray *r)
{
	r->cx = 2.0 * x / (double)WIN_W - 1.0;
	r->rx = m->scn->dirx + m->scn->plx * r->cx;
	r->ry = m->scn->diry + m->scn->ply * r->cx;
	r->ddx = fabs(1.0 / safe_div(r->rx));
	r->ddy = fabs(1.0 / safe_div(r->ry));
	r->mapx = (int)m->scn->px;
	r->mapy = (int)m->scn->py;
}

void	ray_setup_steps(t_mlx *m, t_ray *r)
{
	if (r->rx < 0.0)
	{
		r->stepx = -1;
		r->sdistx = (m->scn->px - r->mapx) * r->ddx;
	}
	else
	{
		r->stepx = 1;
		r->sdistx = (r->mapx + 1.0 - m->scn->px) * r->ddx;
	}
	if (r->ry < 0.0)
	{
		r->stepy = -1;
		r->sdisty = (m->scn->py - r->mapy) * r->ddy;
	}
	else
	{
		r->stepy = 1;
		r->sdisty = (r->mapy + 1.0 - m->scn->py) * r->ddy;
	}
}

int	is_oob_or_wall(t_mlx *m, t_ray *r)
{
	if (r->mapx < 0 || r->mapy < 0)
		return (1);
	if (r->mapx >= m->scn->map_w || r->mapy >= m->scn->map_h)
		return (1);
	if (m->scn->map[r->mapy][r->mapx] == '1')
		return (1);
	return (0);
}
