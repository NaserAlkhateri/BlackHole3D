/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalkhate <nalkhate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:48:42 by nalkhate          #+#    #+#             */
/*   Updated: 2023/11/17 11:01:07 by nalkhate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*list_head;

	if (lst == NULL || !f || !del)
		return (NULL);
	list_head = ft_lstnew(f(lst->content));
	if (!list_head)
		return (NULL);
	new_list = list_head;
	while (lst->next != NULL)
	{
		lst = lst->next;
		new_list->next = ft_lstnew(f(lst->content));
		if (!new_list->next)
		{
			ft_lstclear(&list_head, del);
			return (NULL);
		}
		new_list = new_list->next;
	}
	return (list_head);
}
