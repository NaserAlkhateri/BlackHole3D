/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:28 by amersha           #+#    #+#             */
/*   Updated: 2025/08/16 12:55:57 by amersha          ###   ########.fr       */
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
		rstrip(p);
		if (!*p)
			return (-1); /* empty path -> error */
		if (!ft_strncmp(ln, "NO", 2))
		{
			if (scn->tex_no) return (-1); /* duplicate */
			scn->tex_no = ft_strdup(p);
			return (0);
		}
		if (!ft_strncmp(ln, "SO", 2))
		{
			if (scn->tex_so) return (-1);
			scn->tex_so = ft_strdup(p);
			return (0);
		}
		if (!ft_strncmp(ln, "WE", 2))
		{
			if (scn->tex_we) return (-1);
			scn->tex_we = ft_strdup(p);
			return (0);
		}
		if (!ft_strncmp(ln, "EA", 2))
		{
			if (scn->tex_ea) return (-1);
			scn->tex_ea = ft_strdup(p);
			return (0);
		}
	}
	return (1);
}

const char	*parse_scene(const char *path, t_scene *scn)
{
	int		fd;
	char	*ln;
	int		got_f;
	int		got_c;
	char	*acc;
	int		r;

	if (!path || !scn)
		return ("Invalid arguments");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ("Cannot open file");
	got_f = 0;
	got_c = 0;
	acc = NULL;
	scn->tex_no = NULL;
	scn->tex_so = NULL;
	scn->tex_we = NULL;
	scn->tex_ea = NULL;
	while ((ln = get_next_line(fd)))
	{
		r = parse_texline(ln, scn);
		if (r == 0)
			;
		else if (r == -1)
			return (free(ln), close(fd), free(acc), "Duplicate/invalid texture identifier");
		else if (!got_f && !ft_strncmp(ln, "F ", 2))
		{
			if (parse_rgb(ln + 2, &scn->floor_c))
				return (free(ln), close(fd), free(acc), "Invalid floor color");
			got_f = 1;
		}
		else if (!got_c && !ft_strncmp(ln, "C ", 2))
		{
			if (parse_rgb(ln + 2, &scn->ceil_c))
				return (free(ln), close(fd), free(acc), "Invalid ceiling color");
			got_c = 1;
		}
		else
			map_accumulate(&acc, ln);
		free(ln);
	}
	close(fd);
	if (!scn->tex_no || !scn->tex_so || !scn->tex_we || !scn->tex_ea)
		return (free(acc), "Missing texture identifier (NO/SO/WE/EA)");
	if (!got_f)
		return (free(acc), "Missing floor color (F)");
	if (!got_c)
		return (free(acc), "Missing ceiling color (C)");
	/* EARLY file-existence check to avoid opening window then crashing */
	fd = open(scn->tex_no, O_RDONLY);
	if (fd < 0) return (free(acc), "Cannot open texture file: NO");
	close(fd);
	fd = open(scn->tex_so, O_RDONLY);
	if (fd < 0) return (free(acc), "Cannot open texture file: SO");
	close(fd);
	fd = open(scn->tex_we, O_RDONLY);
	if (fd < 0) return (free(acc), "Cannot open texture file: WE");
	close(fd);
	fd = open(scn->tex_ea, O_RDONLY);
	if (fd < 0) return (free(acc), "Cannot open texture file: EA");
	close(fd);
	if (map_finalize(scn, acc))
		return ("Map parsing failed");
	return (NULL);
}
