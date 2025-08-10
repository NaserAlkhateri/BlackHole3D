/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:45:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/10 16:27:00 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_map_char(char c)
{
	if (c == ' ' || c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	map_accumulate(char **acc, char *line)
{
	int		i;
	char	*tmp;
	char	*joined;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (0);
	if (!is_map_char(line[i]))
		return (0);
	tmp = ft_strjoin(line, "\n");
	if (!tmp)
		return (1);
	if (!*acc)
		joined = ft_strdup(tmp);
	else
		joined = ft_strjoin(*acc, tmp);
	free(tmp);
	if (!joined)
		return (1);
	if (*acc)
		free(*acc);
	*acc = joined;
	return (0);
}

static void	pad_and_copy(char **dst, char **src, int h, int w)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	while (i < h)
	{
		len = (int)ft_strlen(src[i]);
		dst[i] = (char *)ft_calloc(w + 1, 1);
		j = 0;
		while (j < w)
		{
			if (j < len)
				dst[i][j] = src[i][j];
			else
				dst[i][j] = ' ';
			j++;
		}
		dst[i][w] = '\0';
		i++;
	}
}

int	map_finalize(t_scene *scn, char *acc)
{
	char	**rows;
	int		i;
	int		w;
	int		j;

	if (!acc)
		return (1);
	rows = ft_split(acc, '\n');
	free(acc);
	if (!rows)
		return (1);
	i = 0;
	w = 0;
	while (rows[i])
	{
		j = (int)ft_strlen(rows[i]);
		if (j > w)
			w = j;
		i++;
	}
	scn->map_h = i;
	scn->map_w = w;
	scn->map = (char **)ft_calloc(scn->map_h + 1, sizeof(char *));
	if (!scn->map)
		return (1);
	pad_and_copy(scn->map, rows, scn->map_h, scn->map_w);
	i = 0;
	while (rows[i])
		free(rows[i++]);
	free(rows);
	return (0);
}
