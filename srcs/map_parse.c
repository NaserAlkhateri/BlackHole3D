/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:45:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/21 23:29:05 by amersha          ###   ########.fr       */
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

int	map_accumulate(char **acc, char *line, int *in_map)
{
	int		i;
	char	*tmp;
	char	*joined;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	
	// If line is empty after trimming
	if (!line[i])
	{
		// If we've already started accumulating map data, this is an error
		if (*acc != NULL)
			return (1);
		// Otherwise, it's just an empty line before the map starts
		return (0);
	}
	
	// Check if this line contains valid map characters
	if (!is_map_char(line[i]))
	{
		// If we've already started accumulating map data, this is an error
		if (*acc != NULL)
			return (1);
		// Otherwise, it's just a non-map line before the map starts
		return (0);
	}
	*in_map = 1;
	// If we get here, this is a valid map line
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

const char *validate_map(t_scene *scn)
{
    int player_count = 0;
    int y, x;

    if (!scn->map)
        return ("Map is not present");

    for (y = 0; y < scn->map_h; y++) {
        for (x = 0; x < scn->map_w; x++) {
            char c = scn->map[y][x];
            if (c != ' ' && c != '0' && c != '1' &&
                c != 'N' && c != 'S' && c != 'E' && c != 'W')
                return ("Invalid character in map");
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                player_count++;
        }
    }

    if (player_count == 0)
        return ("No player start position");
    if (player_count > 1)
        return ("Multiple player start positions");

    for (x = 0; x < scn->map_w; x++) {
        if (scn->map[0][x] != ' ' && scn->map[0][x] != '1')
            return ("Map not closed at top");
        if (scn->map[scn->map_h-1][x] != ' ' && scn->map[scn->map_h-1][x] != '1')
            return ("Map not closed at bottom");
    }

    for (y = 0; y < scn->map_h; y++) {
        if (scn->map[y][0] != ' ' && scn->map[y][0] != '1')
            return ("Map not closed on left");
        if (scn->map[y][scn->map_w-1] != ' ' && scn->map[y][scn->map_w-1] != '1')
            return ("Map not closed on right");
    }

    for (y = 1; y < scn->map_h - 1; y++) {
        for (x = 1; x < scn->map_w - 1; x++) {
            if (scn->map[y][x] == '0' || scn->map[y][x] == 'N' || 
                scn->map[y][x] == 'S' || scn->map[y][x] == 'E' || 
                scn->map[y][x] == 'W') {
                if (scn->map[y-1][x] == ' ' || 
                    scn->map[y+1][x] == ' ' || 
                    scn->map[y][x-1] == ' ' || 
                    scn->map[y][x+1] == ' ')
                    return ("Map has interior hole");
            }
        }
    }

    return (NULL);
}
