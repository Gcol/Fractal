/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 02:13:11 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/19 02:49:00 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"
# include <math.h>

# define WIDTH 750
# define HEIGHT 750

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_modif
{
	int				current;
	long			back;
	double		x_base;
	double		y_base;
	double		zoom;
}					t_modif;

typedef struct		s_img
{
	int				sl;
	int				bpp;
	int				end;
	int				*image;
	int				choice;
	int				iteration_max;
	void			*img_addr;
	double			x[2];
	double			y[2];
	double			x_scale;
	double			y_scale;
	struct s_img	*next;
	struct s_img	*prev;
	t_point			inc;
	t_modif			*modif;
}					t_img;

typedef struct		s_map
{
	void			*mlx;
	void			*win;
	int				**matrice;
	t_img			*img;
}					t_map;

void				re_trace(t_map *map);
void				choose_good_fractale(int choice, t_map *map);
t_map				*create_win();
void				draw_fractal(t_map *map, double x, double y);

#endif
