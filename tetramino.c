/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetramino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:07:38 by mgena             #+#    #+#             */
/*   Updated: 2019/10/16 21:38:38 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

uint64_t	make_tetramino(const char *string)
{
	size_t		i;
	uint64_t	res;
	uint64_t	tmp;

	i = 0;
	tmp = 0;
	res = 0;
	while (i != 19)
	{
		if (string[i] != '#' && string[i] != '.' && string[i] != '\n')
			error();
		if (string[i] == '#')
			res |= (1 << tmp);
		tmp++;
		if (string[i] == '\n')
		{
			res <<= 16;
			tmp = 0;
		}
		i++;
	}
	if (string[20] == '.' || string[20] == '#' || string[0] == 0)
		error();
	return (bit_shift(res));
}

int			get_tetraminos(int fd, t_tetramino tetraminoarr[26])
{
	char	tetrachr[22];
	char	lastchar;
	int		x;

	x = 0;
	ft_bzero(tetrachr, 22);
	while (read(fd, tetrachr, 21) > 0)
	{
		if (x == 26)
			error();
		tetraminoarr[x].cont = make_tetramino(tetrachr);
		tetraminoarr[x].width = tetra_width(tetraminoarr[x].cont);
		tetraminoarr[x].height = tetra_height(tetraminoarr[x].cont);
		lastchar = tetrachr[20];
		ft_bzero(tetrachr, 22);
		x++;
	}
	if (x == 0)
		error();
	if (read < 0)
		error();
	if (lastchar != '\0')
		error();
	return (x);
}

void		get_pos(int i[2], t_tetramino *tet)
{
	tet->x = i[0];
	tet->y = i[1];
}

int			fillit(t_tetramino *tet, t_map *map)
{
	int i[2];

	i[1] = 0;
	if ((*tet).cont == 0)
		return (1);
	while (i[1] + (*tet).height <= map->size)
	{
		i[0] = 0;
		while (i[0] + (*tet).width <= map->size)
		{
			if ((*(uint64_t *)(map->cont + i[1]) & (*tet).cont >> i[0]) == 0)
			{
				*(uint64_t *)(map->cont + i[1]) ^= (*tet).cont >> i[0];
				if (fillit(tet + 1, map) == 1)
				{
					get_pos(i, tet);
					return (1);
				}
				*(uint64_t *)(map->cont + i[1]) ^= (*tet).cont >> i[0];
			}
			i[0]++;
		}
		i[1]++;
	}
	return (0);
}
