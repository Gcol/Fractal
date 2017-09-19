#include <fractol.h>

void  fractal(t_img *img, t_point inc, t_point coord, int pos)
{
	double tmp;
  t_point temp;
	int i;

  if (img->choice == 0)
  {
    temp = inc;
    inc = coord;
    coord = temp;
  }
	i = -1;
	while(inc.x * inc.x + inc.y * inc.y < 4 && ++i < img->iteration_max)
	{
		tmp = inc.x;
    inc.x = ((img->choice == 2) ? fabs(inc.x * inc.x) : inc.x * inc.x)
     - inc.y * inc.y + coord.x;
    inc.y = ((img->choice == 2) ? fabs(2 * inc.y * tmp) : 2 * inc.y * tmp)
      + coord.y;
	}
	if (i == img->iteration_max)
		img->image[pos] = 0xFFFFFF - img->modif->back;
	else if (i < 20)
    img->image[pos] = img->modif->back;
  else
    img->image[pos] = i * (img->modif->back * 100 + 0x00000F) / img->iteration_max * 100;
}

#include <stdio.h>

void draw_fractal(t_map *map, double x, double y)
{
 t_point coord;
  int   k;

  k = -1;
  coord.y = y;
	printf("coord.x = %f | coord.y = %f \nimg->x0 = %f | img->x1 = %f | img->y0 = %f | img->y1 = %f \nimg->x_scale = %lf | img->y_scale = %lf \n\n\n", coord.x, coord.y, map->img->x[0], map->img->x[1], map->img->y[0], map->img->y[1], map->img->x_scale, map->img->y_scale);
  while((float)coord.y < (float)map->img->y[1])
  {
 		coord.x = x;
 		while((float)coord.x < (float)map->img->x[1])
 		{
      fractal(map->img, map->img->inc, coord, ++k);
 			coord.x += map->img->x_scale;
 		}
 		coord.y += map->img->y_scale;
 	}
   mlx_put_image_to_window(map->mlx, map->win, map->img->img_addr, 0, 0);
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
