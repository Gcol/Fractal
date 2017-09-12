#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"
# include <math.h>

# define WIDTH 1000
# define HEIGHT 1000

typedef struct	s_point
{
	double	x;
	double	y;
}								t_point;

typedef struct	s_img
{
	int			sl;
	int			bpp;
	int			end;
	int			*image;
	int			choice;
	int			iteration_max;
	t_point	inc;
	void		*img_addr;
	double		x[2];
	double		y[2];
	double		x_scale;
	double		y_scale;
  struct  t_img   *next;
  struct  t_img   *prev;
	void (*fractal)(struct s_img *, t_point, t_point, int);
}				t_img;

typedef struct	s_modif
{
	int			x_base;
	int			y_base;
	int			z_base;
	double		zoom;
	int			distance;
}				t_modif;

typedef struct	s_map
{
	void		*mlx;
	void		*win;
	int			**matrice;
	int			*len_line;
	int			len;
	t_img		*img;
	t_modif		*modif;
}				t_map;

#endif
