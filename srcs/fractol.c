#include <fractol.h>
#include <stdarg.h>
#include <stdio.h>



/*
   map->img.img_addr = mlx_new_image(map->mlx, map->modif->width,
   map->modif->height);
   map->img.dta = (int *)mlx_get_data_addr(map->img.img_addr,
   &map->img.bpp, &map->img.sl, &map->img.end);
 */

 void draw_fractal(void (*fractal)(t_img *, t_point, t_point, int), t_map *map)
 {
   t_point coord;
   int   k;

   k = -1;
   coord.y = map->img->y[0];
 	while((float)coord.y < (float)map->img->y[1])
 	{
 		coord.x = map->img->x[0];
 		while(coord.x < map->img->x[1])
 		{
 			fractal(map->img, map->img->inc, coord, ++k);
 			coord.x += map->img->x_scale;
 		}
 		coord.y += map->img->y_scale;
 	}
   mlx_put_image_to_window(map->mlx, map->win, map->img->img_addr, 0, 0);
 }


void  Mandelbrot(t_img *img, t_point inc, t_point coord, int pos)
{
	double tmp;
	int i;

	i = -1;
	while(inc.x * inc.x + inc.y * inc.y < 4 && ++i < img->iteration_max)
	{
		tmp = inc.x;
		inc.x = inc.x * inc.x - inc.y * inc.y + coord.x;
		inc.y = 2 * inc.y * tmp + coord.y;
	}
	if (i == img->iteration_max)
		img->image[pos] = 0;
	else
		img->image[pos] = i * 255 / img->iteration_max;
}


void	re_trace(t_map *map)
{
  map->img->x[0] = map->img->x[0] * map->modif->zoom;
  map->img->x[1] = map->img->x[1] * map->modif->zoom;
  map->img->y[0] = map->img->y[0] * map->modif->zoom;
  map->img->y[1] = map->img->y[1] * map->modif->zoom;
  map->img->y_scale = (map->img->y[0] - map->img->y[1]) < 0 ? (map->img->y[1] - map->img->y[0]) / HEIGHT : (map->img->y[0] - map->img->y[1]) / HEIGHT ;
	map->img->x_scale = (map->img->x[0] - map->img->x[1]) < 0 ? (map->img->x[1] - map->img->x[0]) / WIDTH : (map->img->x[0] - map->img->x[1]) / WIDTH ;
	draw_fractal(map->img->fractal, map);
}


int		pressed_key(int keycode, t_map *map)
{
	if (keycode == 53)
		exit(0);
	if ((keycode >= 123 && keycode <= 126) || keycode == 69 ||
			keycode == 78 || keycode == 13 || keycode == 1)
	{
    printf("keycode = %d\n", keycode);
		if (keycode == 1)
			map->modif->zoom -= 1;
		else if (keycode == 13)
			map->modif->zoom += 1;
		else if (keycode == 69)
			map->modif->distance += 1;
		else if (keycode == 78)
			map->modif->distance -= 1;
		else if (keycode == 126)
    	map->modif->zoom = 0.9;
		else if (keycode == 125)
			map->modif->zoom = 1.1;
		else if (keycode == 124)
			map->modif->x_base += 20;
		else if (keycode == 123)
			map->modif->x_base -= 20;
		  re_trace(map);
	}
	return (0);
}

t_map	*create_win()
{
	t_map	*map;

	map = ft_memalloc_exit(sizeof(t_map));
	map->modif = ft_memalloc_exit(sizeof(t_modif));
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, WIDTH, HEIGHT, "Fractol");
	map->img = ft_memalloc_exit(sizeof(t_img));
	map->img->img_addr = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	map->img->image = (int *)mlx_get_data_addr(map->img->img_addr,
			&map->img->bpp, &map->img->sl, &map->img->end);
	mlx_hook(map->win, 2, (1L << 0), &pressed_key, map);
	return(map);
}

char  **ft_create_list_str(int cnt, ...)
{
	va_list lst;
	char **result;
	char *tmp;
	int i;

	va_start(lst, cnt);
	i = 0;
	result = ft_memalloc_exit(sizeof(char **) * (cnt + 1));
	while(i < cnt)
	{
		tmp = va_arg(lst, char *);
		result[i] = ft_strdup(tmp);
		i++;
	}
	return(result);
}

int argument_valid(char *argv)
{
	char **valid_fract;
	int i;
	int rep;

	valid_fract = ft_create_list_str(3, "Julia", "Mandelbrot", "Test");
	i = 0;
	rep = -1;
	while(valid_fract[i])
	{
		if (!ft_strcmp(argv, valid_fract[i]))
			rep = i;
		free(valid_fract[i]);
		i++;
	}
	free(valid_fract);
	return(rep);
}

void init_jump(t_img *img)
{
	if (img->choice == 1)
	{
		img->x[0] = -2.1;
		img->x[1] = 1.2;
		img->y[0] = -1.2;
		img->y[1] = 1.6;
    img->inc.x = 0;
    img->inc.y = 0;
	}
	img->iteration_max = 200;
	img->y_scale = (img->y[0] - img->y[1]) < 0 ? (img->y[1] - img->y[0]) / HEIGHT : (img->y[0] - img->y[1]) / HEIGHT ;
	img->x_scale = (img->x[0] - img->x[1]) < 0 ? (img->x[1] - img->x[0]) / WIDTH : (img->x[0] - img->x[1]) / WIDTH ;
}

void choose_good_fractale(int choice, t_map *map)
{
  void (*fractal[3])(t_img *, t_point, t_point, int);

  fractal[1] = Mandelbrot;
  map->img->fractal = fractal[choice];
	map->img->choice = choice;
	init_jump(map->img);
  draw_fractal(fractal[choice], map);
	if (!map->img->next)
		printf("%d\n", choice);
}


int		main(int argc, char **argv)
{
	t_map *map;
	int   error;
	int   choice;

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
				choose_good_fractale(choice, map);
			}
		}
		if (!error)
			mlx_loop(map->mlx);
	}
	if (error == 1)
		write(2, "Usage : ./fractol (Julia / Mandelbrot)\n", 39);
	return (0);
}
