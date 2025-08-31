/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:34:38 by amersha           #+#    #+#             */
/*   Updated: 2025/08/16 12:59:00 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	zero_imgs(t_mlx *m)
{
	m->img.img = NULL;
	m->no.img = NULL;
	m->so.img = NULL;
	m->we.img = NULL;
	m->ea.img = NULL;
}

int	init_mlx(t_mlx *m, t_scene *scn)
{
	if (!m || !scn)
		return (1);
	zero_imgs(m);
	m->scn = scn;
	m->mlx = mlx_init();
	if (!m->mlx)
		return (1);
	m->win = mlx_new_window(m->mlx, WIN_W, WIN_H, "cub3D");
	if (!m->win)
		return (destroy_and_exit(m, 1), 1);
	m->img.img = mlx_new_image(m->mlx, WIN_W, WIN_H);
	if (!m->img.img)
		return (destroy_and_exit(m, 1), 1);
	m->img.addr = mlx_get_data_addr(m->img.img, &m->img.bpp,
			&m->img.line_len, &m->img.endian);
	m->img.w = WIN_W;
	m->img.h = WIN_H;
	return (0);
}

void	destroy_and_exit(t_mlx *m, int code)
{
	if (!m)
		exit(code);
	free_textures(m);
	if (m->img.img)
		mlx_destroy_image(m->mlx, m->img.img);
	if (m->win)
		mlx_destroy_window(m->mlx, m->win);
	exit(code);
}
