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

int		fractal(t_img *img, t_point inc, t_point coord)
{
	double	tmp;
	int		i;

	i = -1;
	while (inc.x * inc.x + inc.y * inc.y < 4 && ++i < img->iteration_max)
	{
		tmp = inc.x;
		inc.x = inc.x * inc.x - inc.y * inc.y + coord.x;
		inc.y = 2 * inc.y * tmp + coord.y;
	}
	return (i);
}

int		b_fractal(t_img *img, t_point inc, t_point coord)
{
	double	tmp;
	int		i;

	i = -1;
	while (inc.x * inc.x + inc.y * inc.y < 4 && ++i < img->iteration_max)
	{
		tmp = inc.x;
		inc.x = inc.x * inc.x - inc.y * inc.y + coord.x;
		if (inc.x < 0)
			inc.x *= -1;
		inc.y = 2 * inc.y * tmp + coord.y;
		if (inc.y < 0)
			inc.y *= -1;
	}
	return (i);
}

int		c_fractal(t_img *img, t_point inc, t_point coord)
{
	double	tmp;
	int		i;

	i = -1;
	while (inc.x * inc.x + inc.y * inc.y < 4 && ++i < img->iteration_max)
	{
		tmp = inc.x;
		inc.x = inc.x * inc.x - fabs(inc.y * inc.y) + coord.x;
		inc.y = 2 * inc.y * fabs(tmp) + coord.y;
	}
	return (i);
}

void	choose_good_fractal(t_img *img, t_point inc, t_point coord, int pos)
{
	int i;

	if (img->choice == 0)
		i = fractal(img, coord, inc);
	else if (img->choice == 2)
		i = b_fractal(img, inc, coord);
	else if (img->choice == 1 || img->choice == 3)
		i = fractal(img, inc, coord);
	else if (img->choice == 4)
		i = c_fractal(img, inc, coord);
	else
		i = b_fractal(img, coord, inc);
	if (i == img->iteration_max)
		img->image[pos] = 0xFFFFFF - img->modif->back;
	else if (i < 20)
		img->image[pos] = img->modif->back;
	else
		img->image[pos] = i ;
}
