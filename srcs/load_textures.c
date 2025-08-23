/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:05:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/23 21:49:55 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	load_one(void *mlx, t_img *im, char *path)
{
	im->img = mlx_xpm_file_to_image(mlx, path, &im->w, &im->h);
	if (!im->img)
		return (1);
	im->addr = mlx_get_data_addr(im->img, &im->bpp, &im->line_len, &im->endian);
	return (0);
}

const char	*load_textures(t_mlx *m, t_scene *scn)
{
	char	*trimmed_no;
	char	*trimmed_so;
	char	*trimmed_we;
	char	*trimmed_ea;

	if (!m || !scn)
		return ("Invalid arguments");
	
	// Trim whitespace from texture paths
	trimmed_no = ft_strtrim(scn->tex_no, " \t\n\r");
	trimmed_so = ft_strtrim(scn->tex_so, " \t\n\r");
	trimmed_we = ft_strtrim(scn->tex_we, " \t\n\r");
	trimmed_ea = ft_strtrim(scn->tex_ea, " \t\n\r");
	
	if (load_one(m->mlx, &m->no, trimmed_no))
	{
		free(trimmed_no); free(trimmed_so); free(trimmed_we); free(trimmed_ea);
		return ("Cannot open texture file: NO");
	}
	if (load_one(m->mlx, &m->so, trimmed_so))
	{
		free(trimmed_no); free(trimmed_so); free(trimmed_we); free(trimmed_ea);
		return ("Cannot open texture file: SO");
	}
	if (load_one(m->mlx, &m->we, trimmed_we))
	{
		free(trimmed_no); free(trimmed_so); free(trimmed_we); free(trimmed_ea);
		return ("Cannot open texture file: WE");
	}
	if (load_one(m->mlx, &m->ea, trimmed_ea))
	{
		free(trimmed_no); free(trimmed_so); free(trimmed_we); free(trimmed_ea);
		return ("Cannot open texture file: EA");
	}
	
	free(trimmed_no);
	free(trimmed_so);
	free(trimmed_we);
	free(trimmed_ea);
	return (NULL);
}

void	free_textures(t_mlx *m)
{
	if (m->no.img)
		mlx_destroy_image(m->mlx, m->no.img);
	if (m->so.img)
		mlx_destroy_image(m->mlx, m->so.img);
	if (m->we.img)
		mlx_destroy_image(m->mlx, m->we.img);
	if (m->ea.img)
		mlx_destroy_image(m->mlx, m->ea.img);
}
