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
	else if (key == KEY_PLUS)
		obj->center.z = obj->center.z - 1;
	else if (key == KEY_MINUS)
		obj->center.z = obj->center.z + 1;
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
		if ((world->obj_selected == 0
				|| world->obj_selected == obj->id))
			execute_move(obj, key);
		obj = obj->next;
	}
}

void	move_light(t_world *world, int key)
{
	if (key == KEY_LEFT)
		world->light->position.x = world->light->position.x - 1;
	else if (key == KEY_RIGHT)
		world->light->position.x = world->light->position.x + 1;
	else if (key == KEY_DOWN)
		world->light->position.y = world->light->position.y - 1;
	else if (key == KEY_UP)
		world->light->position.y = world->light->position.y + 1;
	else if (key == KEY_PLUS)
		world->light->position.z = world->light->position.z - 1;
	else if (key == KEY_MINUS)
		world->light->position.z = world->light->position.z + 1;
	point_light(&world->light->position, &world->light->intensity, world);
}

void	move_camera(t_minirt *win, int key)
{
	t_camera	*camera;

	camera = &win->camera;
	if (key == KEY_LEFT)
	{
		camera->center.x = camera->center.x - 1;
		camera->direct_center.x = camera->direct_center.x - 1;
	}
	else if (key == KEY_RIGHT)
	{
		camera->center.x = camera->center.x + 1;
		camera->direct_center.x = camera->direct_center.x + 1;
	}
	else if (key == KEY_DOWN)
	{
		camera->center.y = camera->center.y - 1;
		camera->direct_center.y = camera->direct_center.y - 1;
	}
	else if (key == KEY_UP)
	{
		camera->center.y = camera->center.y + 1;
		camera->direct_center.y = camera->direct_center.y + 1;
	}
	else if (key == KEY_PLUS)
	{
		camera->center.z = camera->center.z + 1;
		camera->direct_center.z = camera->direct_center.z + 1;
	}
	else if (key == KEY_MINUS)
	{
		camera->center.z = camera->center.z - 1;
		camera->direct_center.z = camera->direct_center.z - 1;
	}
	clean_matrix(NULL, win->camera.trans, 0);
	printf("to: %f %f %f\n", camera->direct_center.x, camera->direct_center.y, camera->direct_center.z);
	printf("from: %f %f %f\n", camera->center.x, camera->center.y, camera->center.z);
	win->camera.trans = view_transformation(&win->camera.center, \
		&win->camera.direct_center, &camera->up);
	clean_matrix(NULL, win->camera.inver, 0);
	win->camera.inver = mtx_inverse(win, win->camera.trans);
}

/// @brief Move the obj and sets the mlx to display the new image.
/// @param win Main code structure.
/// @param key Key mapping to move the obj.
void	move_win(t_minirt *win, int key)
{
	void	*new_img;

	if (win->world.objs && win->world.scene_elem == OBJECT)
		move_obj(&win->world, key, win->world.obj_selected);
	else if (win->world.scene_elem == CAMERA)
		move_camera(win, key);
	else if (win->world.scene_elem == LIGHT)
		move_light(&win->world, key);
	redo_render(win);
}
