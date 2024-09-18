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

/// @brief Repeat render after transformation on scene elements.
/// @param win Main program structure.
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

/// @brief Check if the key is on program scope.
/// @param key_pressed Key pressed by the user.
/// @return True if its on scope.
bool	key_on_scope(int key_pressed)
{
	return (key_pressed == KEY_LEFT || key_pressed == KEY_RIGHT
		|| key_pressed == KEY_DOWN || key_pressed == KEY_UP
		|| key_pressed == KEY_PLUS || key_pressed == KEY_MINUS
		|| key_pressed == KEY_W || key_pressed == KEY_A
		|| key_pressed == KEY_S || key_pressed == KEY_D
		|| key_pressed == KEY_E || key_pressed == KEY_Q
		|| key_pressed == KEY_L || key_pressed == KEY_C
		|| key_pressed == KEY_O || key_pressed == KEY_TAB
		|| key_pressed == KEY_HOME);
}

/// @brief Check if the key is on movement scope.
/// @param key_pressed Key pressed by the user.
/// @return True if its on movement scope.
bool	key_on_movement(int key_pressed)
{
	return (key_pressed == KEY_LEFT || key_pressed == KEY_RIGHT
		|| key_pressed == KEY_DOWN || key_pressed == KEY_UP
		|| key_pressed == KEY_PLUS || key_pressed == KEY_MINUS
		|| key_pressed == KEY_W || key_pressed == KEY_A
		|| key_pressed == KEY_S || key_pressed == KEY_D
		|| key_pressed == KEY_TAB);
}
