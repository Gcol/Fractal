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

void	init_jump(t_img *img)
{
	if (img->choice == 0 || img->choice == 3)
	{
		img->x[0] = -2;
		img->x[1] = 0.1;
		img->y[0] = -1.5;
		img->y[1] = 1.7;
	}
	else if (img->choice == 1)
	{
		img->x[0] = -3.3;
		img->x[1] = 0;
		img->y[0] = -1.2;
		img->y[1] = 1.6;
	}
	else if (img->choice == 2)
	{
		img->x[0] = -2.5;
		img->x[1] = 1.4;
		img->y[0] = -1.8;
		img->y[1] = 0.6;
	}
	img->iteration_max = 150;
	img->y_scale = (img->y[1] - img->y[0]) / HEIGHT;
	img->x_scale = (img->x[1] - img->x[0]) / WIDTH;
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
				choose_good_fractale(choice, map);
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
