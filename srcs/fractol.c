/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:16:51 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/07 15:19:59 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <stdarg.h>
#include <stdio.h>

/*map->img.img_addr = mlx_new_image(map->mlx, map->modif->width,
  map->modif->height);
  map->img.dta = (int *)mlx_get_data_addr(map->img.img_addr,
  &map->img.bpp, &map->img.sl, &map->img.end);*/
/*
   définir x1 = -2.1
   définir x2 = 0.6
   définir y1 = -1.2
   définir y2 = 1.2
   définir zoom = 100 // pour une distance de 1 sur le plan, on a 100 pixel sur l'image
   définir iteration_max = 50

   définir image_x = (x2 - x1) * zoom
   définir image_y = (y2 - y1) * zoom

   Pour x = 0 tant que x < image_x par pas de 1
   Pour y = 0 tant que y < image_y par pas de 1
   définir c_r = x / zoom + x1
   définir c_i = y / zoom + y1
   définir z_r = 0
   définir z_i = 0
   définir i = 0

   Faire
   définir tmp = z_r
   z_r = z_r*z_r - z_i*z_i + c_r
   z_i = 2*z_i*tmp + c_i
   i = i+1
   Tant que z_r*z_r + z_i*z_i < 4 et i < iteration_max

   si i = iteration_max
   dessiner en noir le pixel de coordonné (x; x)
   sinon
   dessiner avec couleur rgb(0, 0, i*255/iterations_max) le pixel de coordonné (x; x)
   finSi
   finPour
   finPour*/

int		pressed_key(int keycode, t_map *map)
{
	if (keycode == 53)
		exit(0);
	if ((keycode >= 123 && keycode <= 126) || keycode == 69 ||
			keycode == 78 || keycode == 13 || keycode == 1)
	{
		if (keycode == 1)
			map->modif->zoom -= 1;
		else if (keycode == 13)
			map->modif->zoom += 1;
		else if (keycode == 69)
			map->modif->distance += 1;
		else if (keycode == 78)
			map->modif->distance -= 1;
		else if (keycode == 126)
			map->modif->y_base -= 20;
		else if (keycode == 125)
			map->modif->y_base += 20;
		else if (keycode == 124)
			map->modif->x_base += 20;
		else if (keycode == 123)
			map->modif->x_base -= 20;
		//re_trace(map);
	}
	return (0);
}

t_map	*create_win(void)
{
	t_map	*map;

	map = ft_memalloc_exit(sizeof(t_map));
	map->modif = ft_memalloc_exit(sizeof(t_modif));
	map->modif->height = 500;
	map->modif->width = 750;
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, map->modif->width,
			map->modif->height, "Fractol");
	mlx_hook(map->win, 2, (1L << 0), &pressed_key, map);
	return (map);
}

char	**ft_create_list_str(int cnt, ...)
{
	va_list	lst;
	char	**result;
	char	*tmp;

	va_start(lst, cnt);
	result = ft_memalloc_exit(sizeof(char **) * (cnt + 1));
	while (cnt--)
	{
		tmp = va_arg(lst, char *);
		result[cnt] = ft_strdup(tmp);
	}
	return (result);
}

int		argument_valid(char *argv)
{
	char	**valid_fract;
	int		i;
	int		rep;

	valid_fract = ft_create_list_str(3, "Julia", "Mandelbrot", "Test");
	i = 0;
	rep = -1;
	while (valid_fract[i])
	{
		if (!ft_strcmp(argv, valid_fract[i]))
			rep = i;
		free(valid_fract[i]);
		i++;
	}
	free(valid_fract);
	return (rep);
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
				if (error == 1)
				{
					map = create_win();
					error = 0;
				}
			}
		}
		if (!error)
			mlx_loop(map->mlx);
	}
	if (error == 1)
		write(2, "Usage : ./fractol (Julia / Mandelbrot)\n", 39);
	return (0);
}
