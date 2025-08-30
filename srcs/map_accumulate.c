/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_accumulate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:10:43 by amersha           #+#    #+#             */
/*   Updated: 2025/08/30 14:35:13 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/cub3d.h"

static int	skip_ws_idx(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == '\t' || s[i] == '\n'))
		i++;
	return (i);
}

static int	validate_line(const char *line, char **acc)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_map_char(line[i]))
		{
			if (*acc)
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}

static int	acc_append(char **acc, char *line)
{
	char	*joined;

	if (!*acc)
	{
		*acc = ft_strdup(line);
		if (!*acc)
			return (1);
		return (0);
	}
	joined = ft_strjoin(*acc, line);
	if (!joined)
		return (1);
	free(*acc);
	*acc = joined;
	return (0);
}

int	map_accumulate(char **acc, char *line, int *in_map)
{
	int	idx;

	if (!acc || !line || !in_map)
		return (1);
	idx = skip_ws_idx(line);
	if (!line[idx])
		return (0);
	if (validate_line(line, acc))
		return (1);
	*in_map = 1;
	if (acc_append(acc, line))
		return (1);
	return (0);
}
