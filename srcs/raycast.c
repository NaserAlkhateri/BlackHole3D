/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalkhate <nalkhate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:45:00 by amersha           #+#    #+#             */
/*   Updated: 2025/09/06 18:38:52 by nalkhate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ray_dda(t_mlx *m, t_ray *r)
{
	r->side = -1;
	while (r->side == -1)
	{
		if (r->sdistx < r->sdisty)
		{
			r->sdistx += r->ddx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sdisty += r->ddy;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (is_oob_or_wall(m, r))
			break ;
		r->side = -1;
	}
}

static void	ray_project(t_mlx *m, t_ray *r)
{
	int	y0_raw;
	int	y1_raw;

	if (r->side == 0)
		r->pdist = (r->mapx - m->scn->px + (1 - r->stepx) / 2.0)
			/ safe_div(r->rx);
	else
		r->pdist = (r->mapy - m->scn->py + (1 - r->stepy)
				/ 2.0) / safe_div(r->ry);
	r->hh = (int)(WIN_H / clamp_min(r->pdist, 1e-6));
	y0_raw = -r->hh / 2 + WIN_H / 2;
	y1_raw = r->hh / 2 + WIN_H / 2;
	r->y0 = y0_raw;
	if (r->y0 < 0)
		r->y0 = 0;
	r->y1 = y1_raw;
	if (r->y1 >= WIN_H)
		r->y1 = WIN_H - 1;
}

static void	ray_wallx_and_tex(t_mlx *m, t_ray *r)
{
	if (r->side == 0)
		r->wallx = m->scn->py + r->pdist * r->ry;
	else
		r->wallx = m->scn->px + r->pdist * r->rx;
	r->wallx -= floor(r->wallx);
	r->tex = pick_tex(m, r->side, r->rx, r->ry);
}

void	raycast_render(t_mlx *m)
{
	int			x;
	t_ray		r;
	t_colargs	a;

	x = 0;
	while (x < WIN_W)
	{
		ray_init(m, x, &r);
		ray_setup_steps(m, &r);
		ray_dda(m, &r);
		ray_project(m, &r);
		ray_wallx_and_tex(m, &r);
		a.x = x;
		a.y0 = r.y0;
		a.y1 = r.y1;
		a.line_h_full = r.hh;
		a.y0_raw = -r.hh / 2 + WIN_H / 2;
		a.wallx = r.wallx;
		a.tex = r.tex;
		draw_column(m, &a);
		x++;
	}
}
