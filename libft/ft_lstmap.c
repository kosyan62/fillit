/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 22:54:11 by mgena             #+#    #+#             */
/*   Updated: 2019/09/18 12:40:17 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *lstcpy;
	t_list *res;

	if (lst == NULL || f == NULL)
		return (NULL);
	lstcpy = f(lst);
	lst = lst->next;
	res = lstcpy;
	while (lst != NULL)
	{
		lstcpy->next = f(lst);
		lstcpy = lstcpy->next;
		lst = lst->next;
	}
	return (res);
}
