/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:12:56 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/07 15:16:04 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"

typedef struct		s_img
{
	int				sl;
	int				bpp;
	int				end;
	void			*img_addr;
	int				*dta;
	struct s_img	*next;
	struct s_img	*prev;
}					t_img;

typedef struct		s_modif
{
	int				x_base;
	int				y_base;
	int				z_base;
	double			zoom;
	int				distance;
	int				width;
	int				height;
}					t_modif;

typedef struct		s_map
{
	void			*mlx;
	void			*win;
	int				**matrice;
	int				*len_line;
	int				len;
	char			*path;
	char			clr;
	t_img			img;
	t_modif			*modif;
}					t_map;

#endif
