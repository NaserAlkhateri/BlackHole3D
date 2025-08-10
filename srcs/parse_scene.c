/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:28 by amersha           #+#    #+#             */
/*   Updated: 2025/08/10 16:27:59 by amersha          ###   ########.fr       */
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

static void	rstrip(char *s)
{
	int	len;

	if (!s)
		return ;
	len = (int)ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'
			|| s[len - 1] == '\t' || s[len - 1] == ' ' || s[len - 1] == '\f'
			|| s[len - 1] == '\v'))
	{
		s[len - 1] = '\0';
		len--;
	}
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

static int	parse_texline(char *ln, t_scene *scn)
{
	char	*p;

	p = ln;
	if (!ft_strncmp(p, "NO", 2) || !ft_strncmp(p, "SO", 2)
		|| !ft_strncmp(p, "WE", 2) || !ft_strncmp(p, "EA", 2))
	{
		p += 2;
		while (*p == ' ' || *p == '\t')
			p++;
		rstrip(p); /* <- important: remove newline/spaces from path */
		if (!*p)
			return (1);
		if (!ft_strncmp(ln, "NO", 2) && !scn->tex_no)
			scn->tex_no = ft_strdup(p);
		else if (!ft_strncmp(ln, "SO", 2) && !scn->tex_so)
			scn->tex_so = ft_strdup(p);
		else if (!ft_strncmp(ln, "WE", 2) && !scn->tex_we)
			scn->tex_we = ft_strdup(p);
		else if (!ft_strncmp(ln, "EA", 2) && !scn->tex_ea)
			scn->tex_ea = ft_strdup(p);
		return (0);
	}
	return (1);
}

int	parse_scene(const char *path, t_scene *scn)
{
	int		fd;
	char	*ln;
	int		got_f;
	int		got_c;
	char	*acc;

	if (!path || !scn)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	got_f = 0;
	got_c = 0;
	acc = NULL;
	scn->tex_no = NULL;
	scn->tex_so = NULL;
	scn->tex_we = NULL;
	scn->tex_ea = NULL;
	while ((ln = get_next_line(fd)))
	{
		if (!parse_texline(ln, scn))
			;
		else if (!got_f && !ft_strncmp(ln, "F ", 2)
			&& !parse_rgb(ln + 2, &scn->floor_c))
			got_f = 1;
		else if (!got_c && !ft_strncmp(ln, "C ", 2)
			&& !parse_rgb(ln + 2, &scn->ceil_c))
			got_c = 1;
		else
			map_accumulate(&acc, ln);
		free(ln);
	}
	close(fd);
	if (!scn->tex_no || !scn->tex_so || !scn->tex_we || !scn->tex_ea)
		return (free(acc), 1);
	if (map_finalize(scn, acc))
		return (1);
	return (!(got_f && got_c));
}
