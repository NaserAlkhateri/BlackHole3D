/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:28 by amersha           #+#    #+#             */
/*   Updated: 2025/08/10 15:21:22 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_split(char **sp)
{
	int	i;

	if (!sp)
		return ;
	i = 0;
	while (sp[i])
	{
		free(sp[i]);
		i++;
	}
	free(sp);
}

static int	parse_rgb(const char *s, t_color *out)
{
	char	**sp;
	int		i;
	int		v;

	if (!s || !out)
		return (1);
	sp = ft_split(s, ',');
	if (!sp || !sp[0] || !sp[1] || !sp[2] || sp[3])
		return (free_split(sp), 1);
	out->r = ft_atoi(sp[0]);
	out->g = ft_atoi(sp[1]);
	out->b = ft_atoi(sp[2]);
	i = 0;
	while (i < 3)
	{
		v = out->r;
		if (i == 1)
			v = out->g;
		if (i == 2)
			v = out->b;
		if (v < 0 || v > 255)
			return (free_split(sp), 1);
		i++;
	}
	out->rgb = (out->r << 16) | (out->g << 8) | out->b;
	free_split(sp);
	return (0);
}

int	parse_scene(const char *path, t_scene *scn)
{
	int		fd;
	char	*ln;
	int		got_f;
	int		got_c;

	if (!path || !scn)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	got_f = 0;
	got_c = 0;
	while ((ln = get_next_line(fd)))
	{
		if (!got_f && !ft_strncmp(ln, "F ", 2)
			&& !parse_rgb(ln + 2, &scn->floor_c))
			got_f = 1;
		else if (!got_c && !ft_strncmp(ln, "C ", 2)
			&& !parse_rgb(ln + 2, &scn->ceil_c))
			got_c = 1;
		free(ln);
		if (got_f && got_c)
			break ;
	}
	close(fd);
	return (!(got_f && got_c));
}
