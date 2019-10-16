/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:59:12 by mgena             #+#    #+#             */
/*   Updated: 2019/10/16 22:03:15 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			sqrt_map(int count)
{
	int i;

	i = 1;
	count *= 4;
	while (i * i < count)
		i++;
	return (i);
}

void		fill_map_alpha(uint16_t *tet, char *map, int map_size)
{
	static char	letter;
	int			i;
	int			j;

	i = 0;
	while (i != 4)
	{
		j = 16;
		while (j != 0)
		{
			if ((tet[i] >> (j - 1) & 1) == 1)
				map[16 - j] = letter + 65;
			j--;
		}
		map = map + map_size;
		i++;
	}
	letter++;
}

void		print_ready_map(char map_chr[300], int map_size)
{
	int i;

	i = 1;
	while (map_chr[i] != 0)
	{
		ft_putchar(map_chr[i - 1]);
		if (i % map_size == 0)
			ft_putchar('\n');
		i++;
	}
}

void		fill_ready_map(int map_size, t_tetramino *tet)
{
	char	map_chr[300];
	int		i;
	int		x;

	i = 0;
	x = 0;
	ft_bzero(map_chr, 299);
	while (i != map_size * map_size + 1)
		map_chr[i++] = '.';
	i = 0;
	while (tet[x].cont != 0)
	{
		if (i == tet[x].x + (tet[x].y * map_size))
		{
			fill_map_alpha((uint16_t *)&(tet[x].cont), &map_chr[i], map_size);
			x++;
			i = 0;
		}
		else
			i++;
	}
	print_ready_map(map_chr, map_size);
}

int			main(int argc, char **argv)
{
	int			fd;
	t_tetramino	tetramino_array[26];
	t_map		map;

	if (argc != 2)
		error();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error();
	map.tetramino_count = 0;
	while (map.tetramino_count != 16)
	{
		map.cont[map.tetramino_count] = 0;
		map.tetramino_count++;
	}
	map.tetramino_count = 0;
	while (map.tetramino_count != 27)
		tetramino_array[map.tetramino_count++].cont = 0;
	map.tetramino_count = get_tetraminos(fd, tetramino_array);
	map.size = sqrt_map(map.tetramino_count);
	while (fillit(tetramino_array, &map) != 1)
		map.size++;
	fill_ready_map(map.size, tetramino_array);
	return (0);
}
