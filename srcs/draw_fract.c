/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 06:38:13 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/24 20:49:12 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	print_help(t_map *map)
{
	char	*src[7];
	int		i;

	i = 0;
	src[0] = "Help :";
	src[1] = "Touche fleche pour le deplacement";
	src[2] = "W et S pour changer les couleurs";
	src[3] = "Molette de la souris et clique pour zoomer et dezoomer";
	src[4] = "A et D pour changer de fractal si il y en a plusieur";
	src[5] = "H pour afficher enlever et afficher l annonce d aide";
	src[6] = "Espace pour figer la souris \
dans les fractale utilisant la souris";
	while (i < 7)
	{
		mlx_string_put(map->mlx, map->win, 15, (i + 1) * 15, 0, src[i]);
		i++;
	}
}

void	draw_fractal(t_map *map, double x, double y)
{
	t_point	coord;
	int		k;

	k = -1;
	coord.y = map->img->y[0];
	while (k / HEIGHT < HEIGHT)
	{
		if ((k + 1) % WIDTH == 0)
		{
			coord.y = map->img->y[0] + ++y * map->img->y_scale;
			coord.x = map->img->x[0];
			x = 0;
		}
		choose_good_fractal(map->img, map->img->inc, coord, ++k);
		coord.x = map->img->x[0] + ++x * map->img->x_scale;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img->img_addr, 0, 0);
	if (map->img->modif->help == 0)
		print_help(map);
}

void	re_trace(t_map *map)
{
	ft_memset(map->img->image, 0, WIDTH * HEIGHT * 4);
	mlx_put_image_to_window(map->mlx, map->win, map->img->img_addr, 0, 0);
	map->img->x[0] += map->img->modif->x_base;
	map->img->x[1] += map->img->modif->x_base;
	map->img->y[0] += map->img->modif->y_base;
	map->img->y[1] += map->img->modif->y_base;
	map->img->modif->zoom = 1;
	map->img->modif->x_base = 0;
	map->img->modif->y_base = 0;
	draw_fractal(map, map->img->x[0], map->img->y[0]);
}
