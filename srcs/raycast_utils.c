/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:45:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/10 16:27:30 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_img	*pick_tex(t_mlx *m, int side, double rx, double ry)
{
	if (side == 0)
	{
		if (rx > 0.0)
			return (&m->ea);
		return (&m->we);
	}
	if (ry > 0.0)
		return (&m->so);
	return (&m->no);
}

int	clampi(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

double	safe_div(double v)
{
	if (v == 0.0)
		return (1e-8);
	return (v);
}

double	clamp_min(double v, double minv)
{
	if (v <= minv)
		return (minv);
	return (v);
}

int	sample_tex_color(t_img *t, int tx, int ty)
{
	char	*px;

	px = t->addr + ty * t->line_len + tx * (t->bpp / 8);
	return (*(int *)px);
}
