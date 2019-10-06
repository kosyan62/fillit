/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 10:30:13 by mgena             #+#    #+#             */
/*   Updated: 2019/09/18 14:10:20 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_line(const char *s, char c, char *res)
{
	size_t i;

	i = 0;
	while (*s != c && *s != '\0')
	{
		res[i] = *s;
		i++;
		s++;
	}
	res[i] = '\0';
	return (i);
}

static const char	*ft_jump(const char *s, char c)
{
	while (*s == c && *s != '\0')
		s++;
	return (s);
}

char				**ft_strsplit(char const *s, char c)
{
	size_t	k;
	char	**res;

	if (s == NULL)
		return (NULL);
	s = ft_jump(s, c);
	res = ft_memalloc(sizeof(char*) * ft_wordcount(s, c) + 1);
	if (res == NULL)
		return (NULL);
	k = 0;
	while (*s != '\0')
	{
		s = ft_jump(s, c);
		res[k] = ft_strnew(ft_strclen(s, c));
		if (res[k] == NULL)
		{
			ft_abortalloc(res, k);
			return (NULL);
		}
		s += ft_line(s, c, res[k++]);
		s = ft_jump(s, c);
		if (*s == '\0')
			res[k] = NULL;
	}
	return (res);
}
