/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalkhate <nalkhate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:44:07 by nalkhate          #+#    #+#             */
/*   Updated: 2023/11/05 13:43:36 by nalkhate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*duped;
	int		i;

	i = 0;
	size = ft_strlen(s1);
	duped = malloc(size + 1);
	if (duped == NULL)
		return (0);
	while (s1[i] != '\0')
	{
		duped[i] = s1[i];
		i++;
	}
	duped[i] = '\0';
	return (duped);
}
