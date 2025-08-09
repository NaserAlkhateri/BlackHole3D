/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalkhate <nalkhate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:48:47 by nalkhate          #+#    #+#             */
/*   Updated: 2023/11/17 18:44:52 by nalkhate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	i_len(long long nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
		return (11);
	else if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static int	divide_by(unsigned int power)
{
	unsigned int		result;

	result = 1;
	while (power > 1)
	{
		result *= 10;
		power--;
	}
	return (result);
}

static void	populate(unsigned int nb, char *c_num)
{
	unsigned int		len;
	unsigned int		digit;
	unsigned int		i;

	i = 0;
	digit = 0;
	len = i_len(nb);
	while (len > 0)
	{
		digit = (nb / divide_by(len));
		nb -= (digit * divide_by(len));
		c_num[i] = digit + 48;
		i++;
		len--;
	}
	c_num[i] = '\0';
}

char	*ft_itoa(int n)
{
	char			*ret;
	int				i;

	i = 0;
	if (n == 0)
	{
		ret = (char *)malloc(2 * sizeof(char));
		if (!ret)
			return (NULL);
		ret[0] = '0';
		ret[1] = '\0';
		return (ret);
	}
	ret = (char *)malloc((i_len(n) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	if (n < 0)
	{
		ret[i++] = '-';
		populate(-1 * n, ret + 1);
	}
	else
		populate(n, ret);
	return (ret);
}
