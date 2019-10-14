/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:39:51 by mgena             #+#    #+#             */
/*   Updated: 2019/09/30 18:34:30 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

void fill_map_alpha(u_int16_t *tet, char *map, int i);

void print_tetramino(const u_int16_t *tet)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 15; j >= 0; j--) {
			printf("%d", tet[i] >> j & 1);
		}
		printf("\n");
	}
	printf("\n");
}

void    print_map(const u_int16_t *array) {
	for (int i = 0; i < 16; i++) {
		for (int j = 15; j >= 0; j--) {
			printf("%d", array[i] >> j & 1);
		}
		printf("\n");
	}
}

void error(void)
{
    ft_putstr("error\n");
    exit(0);
}

u_int64_t bit_shift(u_int64_t tet)
{
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

u_int64_t    make_tetramino(const char *string)
{
    u_int64_t res;
    u_int64_t tmp;
	size_t i;

	i = 0;
    tmp = 0;
    res = 0;
    while (i != 19)
    {
        if (string[i] == '#')
            res = res | (1 << tmp);
        if (string[i++] == '\n')
        {
            res = res << 16;
            tmp = 0;
        }
        else
	        tmp++;
    }
	res = reverse_bits_64(res);
	res = bit_shift(res);
    return (res);
}

int 	get_tetraminos(int fd, t_tetramino tetraminoarr[26])
{
	char tetrachr[22];
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
		x++;
	}
	if (tetrachr[21] == '\n')
		error();
	return (x);
}

int sqrt_map(int count)
{
	int i;

	i = 1;
	count *= 4;
	while (i * i <= count)
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
				*(u_int64_t *) (map->content + k) ^= (*tetramins).content >> i;
			}
			i++;
		}
		k++;
	}
		return (0);

}
void print_ready_map(int map_size, t_tetramino *tet)
{
	char map_chr[300];
	int i = 0;
//	int j = 15;
	int x = 0;
//	char c = 65;
	ft_bzero(map_chr, 299);
	while (i != map_size * map_size)
		map_chr[i++] = '.';
	i = 0;
//	printf("map size is %d\n", map_size);
	while ((tet[i]).content != 0)
	{
//		printf("coordinates %d: %d:%d\n", i, tet[i].x, tet[i].y);
		i++;
	}
	i = 0;
	while (tet[x].content != 0)
	{
			if(i == tet[x].x + (tet[x].y * map_size))
			{
				fill_map_alpha((u_int16_t *) &(tet[x].content), &map_chr[i], map_size);
				x++;
				i = 0;
			}
			else i++;
	}
	i = 1;
	while (map_chr[i] != 0)
	{
		ft_putchar(map_chr[i - 1]);
		if (i % map_size == 0)
			ft_putchar('\n');
		i++;
	}
//	i = 0;
//	while (array[i].content != 0)
//	{
//		x = array[i].x + array[i].y * map.size;
//	}
//	while (i < 16)
//	{
//		j = 15;
//		while (j >= 0)
//		{
//			if ((map.content[i] >> j & 1) == 1)
//				map_chr[x] = c;
//				ft_putchar('1');
//			else
//				map_chr[x] = '0';
//				ft_putchar('0');
//			j--;
//			x++;
//		}
//		ft_putchar('\n');
//		i++;
//		x++;
//	}
//	printf("%s", map_chr);
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
int main(void)
{
	int fd;
	t_tetramino	tetramino_array[26];
	t_map map;


	fd = open("test", O_RDONLY);
	map.tetramino_count = 0;
	while (map.tetramino_count != 26)
		tetramino_array[map.tetramino_count++].content = 0;
    map.tetramino_count = get_tetraminos(fd, tetramino_array);
	map.size = sqrt_map(map.tetramino_count);
	while (fillit(tetramino_array, &map) != 1)
			map.size++;
//	print_map(map.content);
//	printf("------------------------\n");
	print_ready_map(map.size, tetramino_array);
    return 0;
}