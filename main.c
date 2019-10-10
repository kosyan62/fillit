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
	printf( "%d\n", x);
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


int fillit(t_tetramino *tetramins, int size_map, u_int16_t map[16])
{
	u_int16_t *tmp;
	int i;
	int k;


	k  = 0;
	tmp = map;
	if ((*tetramins).content == 0)
		return 1;
	while (k + (*tetramins).height <= size_map)
	{
		i = 0;
		while (i + (*tetramins).width <= size_map)
		{
			if ((*(u_int64_t *)(map + k) & (*tetramins).content >> i) == 0)
			{
				*(u_int64_t *) (map + k) ^= (*tetramins).content >> i;
				if (fillit(tetramins + 1, size_map, tmp) == 1)
				{
					tetramins->x = i;
					tetramins->y = k;
					return 1;
				}
				*(u_int64_t *) (map + k) ^= (*tetramins).content >> i;
			}
			i++;
		}
		k++;
	}
		return (0);

}
void print_ready_map(u_int16_t map)
{

}

int main(void)
{
	int fd;
	t_tetramino	tetramino_array[26];
	u_int16_t map[16];
	int tetramino_count;
	int size_map;

	fd = open("test", O_RDONLY);
	tetramino_count = 0;
	while (tetramino_count != 26)
		tetramino_array[tetramino_count++].content = 0;
    tetramino_count = get_tetraminos(fd, tetramino_array);
	size_map = sqrt_map(tetramino_count);
	while (fillit(tetramino_array, size_map, map) != 1)
			size_map++;
	print_map(map);
    return 0;
}