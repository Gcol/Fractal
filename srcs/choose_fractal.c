/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_fractal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 20:50:43 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/25 10:20:31 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static	double	ft_dabs(double value)
{
	if (value < 0)
		return (-value);
	return (value);
}

static	int		fractal(t_img *img, t_point inc, t_point coord, int multip)
{
	double	tmp;
	int		i;

	i = -1;
	while (inc.x * inc.x + inc.y * inc.y < 4 && ++i < img->iteration_max)
	{
		tmp = inc.x;
		inc.x = inc.x * inc.x - inc.y * inc.y + coord.x;
		inc.y = multip * inc.y * tmp + coord.y;
	}
	return (i);
}

static	int		b_fractal(t_img *img, t_point inc, t_point coord, int multip)
{
	double	tmp;
	int		i;

	i = -1;
	while (inc.x * inc.x + inc.y * inc.y < 4 && ++i < img->iteration_max)
	{
		tmp = inc.x;
		inc.x = ft_dabs(inc.x * inc.x) - inc.y * inc.y + coord.x;
		inc.y = multip * ft_dabs(inc.y * tmp) + coord.y;
	}
	return (i);
}

static	int		c_fractal(t_img *img, t_point inc, t_point coord, int multip)
{
	double	tmp;
	int		i;

	i = -1;
	while (inc.x * inc.x + inc.y * inc.y < 4 && ++i < img->iteration_max)
	{
		tmp = inc.x;
		inc.x = inc.x * inc.x - ft_dabs(inc.y * inc.y) + coord.x;
		inc.y = multip * inc.y * ft_dabs(tmp) + coord.y;
	}
	return (i);
}

void			choose_fractal(t_img *img, t_point inc, t_point coord, int pos)
{
	int i;

	if (img->choice == 0)
		i = fractal(img, coord, inc, 2);
	else if (img->choice == 1 || img->choice == 2)
		i = fractal(img, inc, coord, 2 * ((img->choice == 1) ? 1 : -1));
	else if (img->choice == 3)
		i = c_fractal(img, inc, coord, 2);
	else if (img->choice == 4)
		i = fractal(img, coord, inc, -2);
	else if (img->choice == 5)
		i = b_fractal(img, inc, coord, 2);
	else if (img->choice == 6)
		i = c_fractal(img, inc, coord, -2);
	else if (img->choice == 7)
		i = b_fractal(img, coord, inc, 2);
	else
		i = c_fractal(img, coord, inc, 2 * ((img->choice == 8) ? 1 : -1));
	if (i == img->iteration_max)
		img->image[pos] = 0x00FFFFFF - img->modif->back;
	else if (i < 20)
		img->image[pos] = img->modif->back;
	else
		img->image[pos] = i * img->modif->back | 0x000000FF;
}
