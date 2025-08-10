/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalkhate <nalkhate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:42:49 by nalkhate          #+#    #+#             */
/*   Updated: 2025/08/10 15:41:43 by nalkhate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*malloc_result(t_list *lst)
{
	int		total_sz;
	char	*res;

	total_sz = 0;
	while (lst != NULL)
	{
		total_sz += ft_strlen(lst->content);
		lst = lst->next;
	}
	res = (char *)malloc((total_sz + 1) * sizeof(char));
	return (res);
}

static char	*ft_gnl_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	while (*s1)
		joined[i++] = *s1++;
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = '\0';
	return (joined);
}

char	*concatenate_list(t_list **lst)
{
	t_list	*current;
	char	*result;
	char	*temp;

	current = *lst;
	if (!current)
		return (NULL);
	result = malloc_result(current);
	if (!result)
	{
		ft_gnl_lstclear(lst);
		return (NULL);
	}
	result[0] = '\0';
	while (current != NULL)
	{
		temp = ft_gnl_strjoin(result, current->content);
		free(result);
		result = temp;
		if (!result)
			return (ft_gnl_lstclear(lst), NULL);
		current = current->next;
	}
	ft_gnl_lstclear(lst);
	return (result);
}
