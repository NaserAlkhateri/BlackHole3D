/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:22 by amersha           #+#    #+#             */
/*   Updated: 2025/08/10 16:27:35 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_pixel(t_img *im, int x, int y, int color)
{
	char	*dst;

	if (!im || x < 0 || y < 0 || x >= im->w || y >= im->h)
		return ;
	dst = im->addr + (y * im->line_len + x * (im->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static void	draw_bg(t_mlx *m)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		color = m->scn->ceil_c.rgb;
		if (y >= WIN_H / 2)
			color = m->scn->floor_c.rgb;
		while (x < WIN_W)
		{
			put_pixel(&m->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_frame(t_mlx *m)
{
	if (!m)
		return ;
	draw_bg(m);
	raycast_render(m);
	mlx_put_image_to_window(m->mlx, m->win, m->img.img, 0, 0);
}
