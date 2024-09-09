/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:14:34 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/02 20:50:47 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
 * takes as argument the addres of the canvas to initialize the mlx connection
 * canvas->mlx: stabilish a connection with the correct grafical system
 * canvas->win: creates a new window.
 * canvas->img: start a new image.
 * canvas->addr: this will set the address accordingly for each pixel.
*/
void	start_mlx(t_canvas	*canvas)
{
	canvas->mlx = mlx_init();
	canvas->win = mlx_new_window(canvas->mlx, WIDTH, HEIGTH, "MiniRT");
	canvas->img = mlx_new_image(canvas->mlx, WIDTH, HEIGTH);
	canvas->addr = mlx_get_data_addr(canvas->img,
			&canvas->bits_per_pixel, &canvas->line_length, &canvas->endian);
}

/*
 * Arguments:
 * 		pointer to a canvas.
 * 		point x, and y, in the window,
 * 		a tupple color
*/
void	write_pixel(t_canvas *canvas, int x, int y, t_color *color)
{
	char	*pixel;

	pixel = canvas->addr
		+ (y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
	*(int *)pixel = map_color(color->r) << 16
		| map_color(color->g) << 8 | map_color(color->b);
}

/*
 * map the floating value from 0-1 to a integer 0-255
*/
int	map_color(float c)
{
	if (c <= 0)
		return (0);
	else if (c >= 1)
		return (255);
	else
		return (c * 255);
}
