/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:34:33 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/09 15:34:34 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Execute the movement of the obj.
/// @param obj Obj to be moved.
/// @param key Key mapping to move the obj.
void	execute_move(t_shape *obj, int key)
{
	if (key == KEY_LEFT)
		obj->center.x = obj->center.x - 1;
	else if (key == KEY_RIGHT)
		obj->center.x = obj->center.x + 1;
	else if (key == KEY_DOWN)
		obj->center.y = obj->center.y - 1;
	else if (key == KEY_UP)
		obj->center.y = obj->center.y + 1;
	mtx_translation(obj->mtx_trans, &obj->center);
	clean_matrix(NULL, obj->mtx_inver, 0);
	obj->mtx_inver = mtx_inverse(NULL, obj->mtx_trans);
}

/// @brief Move the object selected.
/// @param world Main code structure.
/// @param key Key mapping to move the obj.
/// @param obj_selected Obj selected to be moved.
void	move_obj(t_world *world, int key, int obj_selected)
{
	t_shape	*obj;

	obj = world->objs;
	(void)obj_selected;
	while (obj)
	{
		if (world->obj_selected == 0
			|| world->obj_selected == obj->id)
			execute_move(obj, key);
		obj = obj->next;
	}
}

/// @brief Move the obj and sets the mlx to display the new image.
/// @param win Main code structure.
/// @param key Key mapping to move the obj.
void	move_win(t_minirt *win, int key)
{
	void	*new_img;

	move_obj(&win->world, key, win->world.obj_selected);
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
