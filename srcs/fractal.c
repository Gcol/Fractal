/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 02:12:45 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/19 03:03:34 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <math.h>

int		argument_valid(char *argv)
{
	if (ft_strcmp(argv, "Julia") == 0)
		return (0);
	else if (ft_strcmp(argv, "Mandelbrot") == 0)
		return (1);
	else if (ft_strcmp(argv, "Perso") == 0)
		return (2);
	else if (ft_strcmp(argv, "Mandelbrot1") == 0)
		return (3);
	return (-1);
}

void	init_fractale(int choice, t_map *map)
{
	struct s_img *tmp;

	tmp = NULL;
	if (map->img)
		tmp = map->img;
	map->img = ft_memalloc_exit(sizeof(t_img));
	map->img->img_addr = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	map->img->image = (int *)mlx_get_data_addr(map->img->img_addr,
			&map->img->bpp, &map->img->sl, &map->img->end);
	map->img->modif = ft_memalloc_exit(sizeof(t_modif));
	map->img->choice = choice;
	map->img->modif->back = 0xB82010;
	map->img->x[0] = -2;
	map->img->x[1] = 2;
	map->img->y[0] = -1.5;
	map->img->y[1] = 1.7;
	map->img->iteration_max = 250;
	map->img->y_scale = (map->img->y[1] - map->img->y[0]) / (double)HEIGHT;
	map->img->x_scale = (map->img->x[1] - map->img->x[0]) / (double)WIDTH;
	draw_fractal(map, 0, 0);
	if (tmp)
		tmp->next = map->img;
	map->img->prev = tmp;
}

int		main(int argc, char **argv)
{
	t_map	*map;
	int		error;
	int		choice;

	error = 1;
	if (argc > 1)
	{
		while (--argc)
		{
			if ((choice = argument_valid(argv[argc])) >= 0)
			{
				if (error == 1 && (map = create_win()))
					error = 0;
				init_fractale(choice, map);
			}
		}
		if (!error)
			mlx_loop(map->mlx);
	}
	if (error == 1)
		write(2, "Usage : ./fractol (Julia / Mandelbrot/ \
Perso / Mandelbrot1)\n", 60);
	return (0);
}
