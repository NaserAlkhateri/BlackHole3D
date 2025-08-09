/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalkhate <nalkhate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:27:36 by nalkhate          #+#    #+#             */
/*   Updated: 2023/11/11 20:39:07 by nalkhate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	chr;

	chr = c;
	len = ft_strlen((char *) s);
	while (len >= 0)
	{
		if (chr == s[len])
			return ((char *) s + len);
		len--;
	}
	return (NULL);
}
