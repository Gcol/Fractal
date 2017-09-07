#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"

typedef struct	s_img
{
	int			sl;
	int			bpp;
	int			end;
	void		*img_addr;
	int			*dta;
  struct  t_img   *next;
  struct  t_img   *prev;
}				t_img;

typedef struct	s_modif
{
	int			x_base;
	int			y_base;
	int			z_base;
	double		zoom;
	int			distance;
	int			width;
	int			height;
}				t_modif;

typedef struct	s_map
{
	void		*mlx;
	void		*win;
	int			**matrice;
	int			*len_line;
	int			len;
	char		*path;
	char		clr;
	t_img		img;
	t_modif		*modif;
}				t_map;


#endif
