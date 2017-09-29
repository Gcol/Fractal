/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 02:12:59 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/25 10:18:10 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static 	int		scroll(int button, int x, int y, t_map *map)
{
	if (button > 0 && button < 6 && button != 3)
	{
		if (button == 5 || button == 2)
			map->img->modif->zoom = 1 / 1.2;
		if (button == 4 || button == 1)
			map->img->modif->zoom = 1.2;
	}
	map->img->modif->x_base = (double)x * map->img->x_scale + map->img->x[0];
	map->img->modif->y_base = (double)y * map->img->y_scale + map->img->y[0];
	map->img->x[0] *= map->img->modif->zoom;
	map->img->x[1] *= map->img->modif->zoom;
	map->img->y[0] *= map->img->modif->zoom;
	map->img->y[1] *= map->img->modif->zoom;
	map->img->y_scale *= map->img->modif->zoom;
	map->img->x_scale *= map->img->modif->zoom;
	map->img->modif->y_base -= map->img->modif->y_base * map->img->modif->zoom;
	map->img->modif->x_base -= map->img->modif->x_base * map->img->modif->zoom;
	re_trace(map);
	return (0);
}

static	int		get_mouse_position(int x, int y, t_map *map)
{
	if (map->img->choice == 0 || map->img->choice == 3 || map->img->choice == 4
		|| map->img->choice == 7 || map->img->choice == 8 || map->img->choice == 9)
		if (map->img->modif->current == 0)
		{
			if (((float)map->img->x_scale * WIDTH) > 2)
			{
				map->img->inc.x = x * ((double)2.4 / WIDTH) - 1.7;
				map->img->inc.y = y * ((double)2 / HEIGHT) - 1;
			}
			else
			{
				map->img->inc.x = x * map->img->x_scale + map->img->x[0];
				map->img->inc.y = y * map->img->y_scale + map->img->y[0];
			}
			re_trace(map);
		}
	return (0);
}

#include <stdio.h>

static	int		pressed_key(int key, t_map *map)
{
	if (key == 53)
		exit(0);
	if ((key >= 123 && key <= 126) || key == 49 || key == 4 ||	key == 13 ||
		key == 1 || key == 2 || key == 0 || key == 0 || key == 15)
	{
		if (key == 1 || key == 13 )
			map->img->modif->back += ((0x00000F | 0x000000FF) * ((key == 1) ? 1 : -1));
		else if (key == 4)
			map->img->modif->help = !(map->img->modif->help);
		else if (key == 0 && (map->img->next) != NULL)
			map->img = map->img->next;
		else if (key == 2 && (map->img->prev) != NULL)
			map->img = map->img->prev;
		else if (key == 49)
			map->img->modif->current = !(map->img->modif->current);
		else if (key == 126 || key == 125)
			map->img->modif->y_base = map->img->y_scale * (double)HEIGHT / 10
				* ((key == 126) ? 1 : -1);
		else if (key == 124 || key == 123)
			map->img->modif->x_base = -map->img->x_scale * (double)WIDTH / 10
				* ((key == 124) ? 1 : -1);
		else if (key == 15)
			init_repere(map);
		re_trace(map);
	}
	return (0);
}

t_map	*create_win(void)
{
	t_map	*map;

	map = ft_memalloc_exit(sizeof(t_map));
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, WIDTH, HEIGHT, "Fractol");
	mlx_hook(map->win, 2, (1L << 0), &pressed_key, map);
	mlx_mouse_hook(map->win, scroll, map);
	mlx_hook(map->win, 6, (1L << 6), &get_mouse_position, map);
	return (map);
}
