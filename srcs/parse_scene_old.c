/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:28 by amersha           #+#    #+#             */
/*   Updated: 2025/08/23 21:30:22 by amersha          ###   ########.fr       */
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

static int	parse_rgb(const char *s, t_color *out) {
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
			return (-1);
		if (!ft_strncmp(ln, "NO", 2))
		{
			if (scn->tex_no) return (-1);
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

void	init_ps(t_ps *ps, t_scene *scn)
{
	ps->got_f = 0;
	ps->got_c = 0;
	ps->in_map = 0;
	ps->acc = NULL;
	ps->loop_res = NULL;
	scn->tex_no = NULL;
	scn->tex_so = NULL;
	scn->tex_we = NULL;
	scn->tex_ea = NULL;
}

void	invalid_cub(t_ps *ps)
{
	free(ps->ln);
	close(ps->fd);
	free(ps->acc);
}

char	*file_check(t_ps *ps, t_scene *scn)
{
	if (!scn->tex_no || !scn->tex_so || !scn->tex_we || !scn->tex_ea)
		return (free(ps->acc), "Missing texture identifier (NO/SO/WE/EA)");
	if (!ps->got_f)
		return (free(ps->acc), "Missing floor color (F)");
	if (!ps->got_c)
		return (free(ps->acc), "Missing ceiling color (C)");
	ps->fd = open(scn->tex_no, O_RDONLY);
	if (ps->fd < 0)
		return (free(ps->acc), "Cannot open texture file: NO");
	close(ps->fd);
	ps->fd = open(scn->tex_so, O_RDONLY);
	if (ps->fd < 0)
		return (free(ps->acc), "Cannot open texture file: SO");
	close(ps->fd);
	ps->fd = open(scn->tex_we, O_RDONLY);
	if (ps->fd < 0)
		return (free(ps->acc), "Cannot open texture file: WE");
	close(ps->fd);
	ps->fd = open(scn->tex_ea, O_RDONLY);
	if (ps->fd < 0)
		return (free(ps->acc), "Cannot open texture file: EA");
	close(ps->fd);
	if (map_finalize(scn, ps->acc))
		return ("Map parsing failed");
	return (NULL);
}


const char	*parse_scene(const char *path, t_scene *scn) {
	t_ps	ps;

	if (!path || !scn)
		return ("Invalid arguments");
	if (!ft_strnstr(path, ".cub", ft_strlen(path)))
		return ("only *.cub files are allowed");
	ps.fd = open(path, O_RDONLY);
	if (ps.fd < 0)
		return ("Cannot open file");
	init_ps(&ps, scn);
	while ((ps.ln = get_next_line(ps.fd)))
	{
		ps.r = parse_texline(ps.ln, scn);
		if (ps.r == 0)
			;
		else if (ps.r == -1)
		{
			invalid_cub(&ps);
			return ("Duplicate/invalid texture identifier");
		}
		else if (!ps.in_map && !ps.got_f && !ft_strncmp(ps.ln, "F ", 2))
		{
			if (parse_rgb(ps.ln + 2, &scn->floor_c))
				return (invalid_cub(&ps), "Invalid floor color");
			ps.got_f = 1;
		}
		else if (!ps.in_map && !ps.got_c && !ft_strncmp(ps.ln, "C ", 2))
		{
			if (parse_rgb(ps.ln + 2, &scn->ceil_c))
				return (invalid_cub(&ps), "Invalid ceiling color");
			ps.got_c = 1;
		}
		else if (!ps.in_map && ps.got_c && !ft_strncmp(ps.ln, "C ", 2))
			return (invalid_cub(&ps), "Ceiling is duplicated!");
		else if (!ps.in_map && ps.got_f && !ft_strncmp(ps.ln, "F ", 2))
			return (invalid_cub(&ps), "Floor is duplicated!");
		else
		{
			ps.map_acc_result = map_accumulate(&(ps.acc), ps.ln, &(ps.in_map));
			if (ps.map_acc_result == 1)
				return (invalid_cub(&ps), "Invalid content in map");
		}
		free(ps.ln);
	}
	close(ps.fd);
	return(file_check(&ps, scn));
}
