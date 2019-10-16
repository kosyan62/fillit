/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:59:12 by mgena             #+#    #+#             */
/*   Updated: 2019/10/16 20:12:59 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		error(void)
{
	ft_putstr("error\n");
	exit(0);
}

void		check_tetramino(uint64_t res)
{
	if (res != 9223512776490647552U &&
		res != 61440 &&
		res != 536928256 &&
		res != 3758104576 &&
		res != 3758129152 &&
		res != 2147540992 &&
		res != 70369817968640 &&
		res != 140739635888128 &&
		res != 211107306291200 &&
		res != 211108380049408 &&
		res != 1073799168 &&
		res != 3758112768 &&
		res != 70371965419520 &&
		res != 140740709613568 &&
		res != 3221274624 &&
		res != 1610661888 &&
		res != 3221250048 &&
		res != 70371965435904 &&
		res != 140740709597184)
		error();
}

uint64_t	bit_shift(uint64_t tet)
{
	tet = reverse_bits_64(tet);
	if (tet == 0)
		error();
	while ((9223512776490647552U & tet) == 0)
		tet <<= 1;
	while ((61440U & tet) == 0)
		tet >>= 16;
	check_tetramino(tet);
	return (tet);
}

int			tetra_width(uint64_t tet)
{
	int w;

	w = 0;
	while ((9223512776490647552U & tet) != 0)
	{
		tet <<= 1;
		w++;
	}
	return (w);
}

int			tetra_height(uint64_t tet)
{
	int l;

	l = 0;
	while ((61440U & tet) != 0)
	{
		tet >>= 16;
		l++;
	}
	return (l);
}

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

int			sqrt_map(int count)
{
	int i;

	i = 1;
	count *= 4;
	while (i * i < count)
		i++;
	return (i);
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
	while (map.tetramino_count != 27)
		tetramino_array[map.tetramino_count++].cont = 0;
	map.tetramino_count = get_tetraminos(fd, tetramino_array);
	map.size = sqrt_map(map.tetramino_count);
	while (fillit(tetramino_array, &map) != 1)
		map.size++;
	fill_ready_map(map.size, tetramino_array);
	return (0);
}
