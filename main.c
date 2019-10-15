/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:59:12 by mgena             #+#    #+#             */
/*   Updated: 2019/10/15 18:59:55 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void fill_map_alpha(u_int16_t *tet, char *map, int i);

void error(void)
{
    ft_putstr("error\n");
    exit(0);
}

u_int64_t bit_shift(u_int64_t tet)
{
	if (tet == 0)
		error();
	while ((9223512776490647552U & tet) == 0)
		tet <<= 1;
	while ((61440U & tet) == 0)
		tet >>= 16;
	return (tet);
}

int tetra_width(u_int64_t tet)
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

int tetra_height(u_int64_t tet)
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

void check_tetramino(u_int64_t res)
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

u_int64_t    make_tetramino(const char *string)
{
    u_int64_t res;
    u_int64_t tmp;
	size_t i;

	i = 0;
    tmp = 0;
    res = 0;
    if (*string == 0)
    	error();
	while (i != 19)
	{
		if (string[i] != '\n')
		{
			if (string[i] != '#' && string[i] != '.')
				error();
			if (string[i] == '#')
				res |= (1 << tmp);
			tmp++;
		}
		else
		{
			res <<= 16;
			tmp = 0;
		}
		i++;
	}
	if (string[20] == '.' || string[20] == '#')
		error();
	res = reverse_bits_64(res);
	res = bit_shift(res);
	check_tetramino(res);
    return (res);
}

int 	get_tetraminos(int fd, t_tetramino tetraminoarr[26])
{
	char tetrachr[22];
	char lastchar;
	int x;

	x = 0;
	ft_bzero(tetrachr, 22);

	while (read(fd, tetrachr, 21) > 0)
	{
		if (x == 27)
			error();
		tetraminoarr[x].content = make_tetramino(tetrachr);
		tetraminoarr[x].width = tetra_width(tetraminoarr[x].content);
		tetraminoarr[x].height = tetra_height(tetraminoarr[x].content);
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

int sqrt_map(int count)
{
	int i;

	i = 1;
	count *= 4;
	while (i * i < count)
		i++;
	return (i);
}

int fillit(t_tetramino *tetramins, t_map *map)
{
	int i;
	int k;


	k  = 0;
	if ((*tetramins).content == 0)
		return 1;
	while (k + (*tetramins).height <= map->size)
	{
		i = 0;
		while (i + (*tetramins).width <= map->size)
		{
			if ((*(u_int64_t *)(map->content + k) & (*tetramins).content >> i) == 0)
			{
				*(u_int64_t *) (map->content + k) ^= (*tetramins).content >> i;
				if (fillit(tetramins + 1, map) == 1)
				{
					tetramins->x = i;
					tetramins->y = k;
					return 1;
				}
				*(u_int64_t *)(map->content + k) ^= (*tetramins).content >> i;
			}
			i++;
		}
		k++;
	}
		return (0);

}
void print_ready_map(int map_size, t_tetramino *tet) {
	char map_chr[300];
	int i = 0;
//	int j = 15;
	int x = 0;
//	char c = 65;
	ft_bzero(map_chr, 299);
	while (i != map_size * map_size + 1)
		map_chr[i++] = '.';
	i = 0;
	while ((tet[i]).content != 0)
	{
		i++;
	}
	i = 0;
	while (tet[x].content != 0)
	{
		if (i == tet[x].x + (tet[x].y * map_size))
		{
			fill_map_alpha((u_int16_t *) &(tet[x].content), &map_chr[i], map_size);
			x++;
			i = 0;
		} else i++;
	}
	i = 1;
	while (map_chr[i] != 0)
	{
		ft_putchar(map_chr[i - 1]);
		if (i % map_size == 0)
			ft_putchar('\n');
		i++;
	}
}

void fill_map_alpha(u_int16_t *tet, char *map, int map_size)
{
	static char letter = 'A';
	int i;
	int j;

	i = 0;
	while (i != 4)
	{
		j = 16;
		while (j != 0)
		{
			if ((tet[i] >> (j - 1) & 1) == 1)
				map[16 - j] = letter;
			j--;
		}
		map = map + map_size;
		i++;
	}
	letter++;
}
int main(int argc, char **argv)
{
	int fd;
	t_tetramino	tetramino_array[26];
	t_map map;

	if (argc != 2)
		error();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error();
	map.tetramino_count = 0;
	while (map.tetramino_count != 26)
		tetramino_array[map.tetramino_count++].content = 0;
    map.tetramino_count = get_tetraminos(fd, tetramino_array);
	map.size = sqrt_map(map.tetramino_count);
	while (fillit(tetramino_array, &map) != 1)
			map.size++;
	print_ready_map(map.size, tetramino_array);
    return 0;
}
