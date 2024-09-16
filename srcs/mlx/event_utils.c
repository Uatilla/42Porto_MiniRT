/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:12:28 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/16 20:12:29 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	redo_render(t_minirt *win)
{
	mlx_destroy_image(win->canvas.mlx, win->canvas.img);
	win->canvas.img = mlx_new_image(win->canvas.mlx, WIDTH, HEIGTH);
	win->canvas.addr = mlx_get_data_addr(win->canvas.img,
			&win->canvas.bits_per_pixel, &win->canvas.line_length,
			&win->canvas.endian);
	render(win);
}

/// @brief Set the obj selected to be moved
/// @param win Main code structure.
void	select_obj(t_minirt *win)
{
	if (++win->world.obj_selected > win->world.n_objs)
		win->world.obj_selected = 0;
}
