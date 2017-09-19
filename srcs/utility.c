/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 02:12:59 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/19 04:00:04 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		scroll(int button, int x, int y, t_map *map)
{

	if (button > 0 && button < 7 && button != 3)
	{
		if (button == 5 || button == 2)
			map->img->modif->zoom = 1/1.2;
		if (button == 4 || button == 1)
			map->img->modif->zoom = 1.2;
		map->img->modif->x_base = x * map->img->x_scale + map->img->x[0];
		map->img->modif->y_base = y * map->img->y_scale + map->img->y[0];
		map->img->x[0] = map->img->x[0] * map->img->modif->zoom;
		map->img->x[1] = map->img->x[1] * map->img->modif->zoom;
		map->img->y[0] = map->img->y[0] * map->img->modif->zoom;
		map->img->y[1] = map->img->y[1] * map->img->modif->zoom;
		map->img->y_scale = (map->img->y[1] - map->img->y[0]) / (float)HEIGHT;
		map->img->x_scale = (map->img->x[1] - map->img->x[0]) / (float)WIDTH ;
		map->img->modif->y_base -= y * map->img->y_scale + map->img->y[0];
		map->img->modif->x_base -= x * map->img->x_scale + map->img->x[0];
		re_trace(map);
	}
	return (0);
}

int get_mouse_position(int x, int y, t_map *map)
{
	if(map->img->choice == 0 || map->img->choice == 3)
		if (map->img->modif->current == 0)
		{
			if (((float)map->img->x_scale * WIDTH) > 2)
			{
				map->img->inc.x = x * ((float)2.4 / WIDTH) - 1.7;
				map->img->inc.y = y * ((float)2 / HEIGHT) - 1;
			}
			else
			{
				map->img->inc.x = x * map->img->x_scale  + map->img->x[0];
				map->img->inc.y = y * map->img->y_scale  + map->img->y[0];
			}
			re_trace(map);
		}
	return(0);
}

int		pressed_key(int keycode, t_map *map)
{
	if (keycode == 53)
		exit(0);
	if ((keycode >= 123 && keycode <= 126) || keycode == 49 ||
			keycode == 13 || keycode == 1 || keycode == 2 || keycode == 0)
	{
		if (keycode == 1)
			map->img->modif->back += 0x00000F;
		else if (keycode == 13 && map->img->modif->back > 0x00000F)
			map->img->modif->back -= 0x00000F;
		else if (keycode == 0 && (map->img->next) != NULL)
			map->img = map->img->next;
		else if (keycode == 2 && (map->img->prev) != NULL)
			map->img = map->img->prev;
		else if (keycode == 49)
			map->img->modif->current = !(map->img->modif->current);
		else if (keycode == 126)
			map->img->modif->y_base = map->img->y_scale * (float)HEIGHT / 10;
		else if (keycode == 125)
			map->img->modif->y_base = -map->img->y_scale * (float)HEIGHT / 10;
		else if (keycode == 124)
			map->img->modif->x_base = -map->img->x_scale * WIDTH / 10;
		else if (keycode == 123)
			map->img->modif->x_base = map->img->x_scale * WIDTH / 10;
		re_trace(map);
	}
	return (0);
}


void choose_good_fractale(int choice, t_map *map)
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
	init_jump(map->img);
	draw_fractal(map, map->img->x[0], map->img->y[0]);
	if (tmp)
		tmp->next = map->img;
	map->img->prev = tmp;
}

t_map	*create_win()
{
	t_map	*map;

	map = ft_memalloc_exit(sizeof(t_map));
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, WIDTH, HEIGHT, "Fractol");
	mlx_hook(map->win, 2, (1L << 0), &pressed_key, map);
	mlx_mouse_hook(map->win, scroll, map);
	mlx_hook(map->win, 6, (1L << 6), &get_mouse_position, map);
	return(map);
}
