/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:25:27 by mgena             #+#    #+#             */
/*   Updated: 2019/09/28 14:44:19 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newlist;
	void	*contentcpy;

	newlist = ft_memalloc(sizeof(t_list));
	if (newlist == NULL)
		return (NULL);
	if (content == NULL || content_size == 0)
	{
		newlist->content = NULL;
		newlist->content_size = 0;
		newlist->next = NULL;
		return (newlist);
	}
	contentcpy = ft_memalloc(content_size);
	if (contentcpy == NULL)
		return (NULL);
	newlist->content = ft_memcpy(contentcpy, content, content_size);
	newlist->content_size = content_size;
	newlist->next = NULL;
	return (newlist);
}
