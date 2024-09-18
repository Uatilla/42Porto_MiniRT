/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:05:47 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/16 20:05:49 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Execute the movement of the obj.
/// @param obj Obj to be moved.
/// @param key Key mapping to move the obj.
void	execute_rotation(t_shape *obj, int key)
{
	t_matrix	*rotation;

	rotation = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(rotation);
	mtx_translation(obj->mtx_trans, &(t_point){0, 0, 0, 1});
	if (key == KEY_Q)
		mtx_rotation_z(rotation, -PI / 12);
	else if (key == KEY_E)
		mtx_rotation_z(rotation, PI / 12);
	else if (key == KEY_D)
		mtx_rotation_y(rotation, PI / 12);
	else if (key == KEY_A)
		mtx_rotation_y(rotation, -PI / 12);
	else if (key == KEY_W)
		mtx_rotation_x(rotation, -PI / 12);
	else if (key == KEY_S)
		mtx_rotation_x(rotation, PI / 12);
	obj->mtx_trans = mtx_multiply(NULL, rotation, obj->mtx_trans);
	mtx_translation(obj->mtx_trans, &obj->center);
	clean_matrix(NULL, obj->mtx_inver, 0);
	obj->mtx_inver = mtx_inverse(NULL, obj->mtx_trans);
}

/// @brief Move the object selected.
/// @param world Main code structure.
/// @param key Key mapping to move the obj.
/// @param obj_selected Obj selected to be moved.
void	rotate_obj_running(t_world *world, int key, int obj_selected)
{
	t_shape	*obj;

	obj = world->objs;
	(void)obj_selected;
	while (obj)
	{
		if ((world->obj_selected == 0
				|| world->obj_selected == obj->id))
			execute_rotation(obj, key);
		obj = obj->next;
	}
}

void	rotate_win(t_minirt *win, int key)
{
	(void)win;
	if (win->world.objs && win->world.scene_elem == OBJECT)
		rotate_obj_running(&win->world, key, win->world.obj_selected);
	else if (win->world.scene_elem == CAMERA)
		rotate_camera(win, key);
	else if (win->world.scene_elem == LIGHT)
	{
		printf("\tERROR: Lights can't rotate.\n");
		return ;
	}
	redo_render(win);
}
