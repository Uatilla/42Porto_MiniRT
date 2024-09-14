/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:47:42 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/04 15:47:44 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	close_window(t_minirt *win)
{
	if (win)
	{
		printf("YES\n");
		if (win->canvas.img)
			mlx_destroy_image(win->canvas.mlx, win->canvas.img);
		printf("YES\n");
		mlx_destroy_window(win->canvas.mlx, win->canvas.win);
		mlx_destroy_display(win->canvas.mlx);
		free(win->canvas.mlx);
		clean_world(&win->world);
		clean_matrix(win, win->camera.trans, 0);
		clean_matrix(win, win->camera.inver, 0);
		clear_exit(win, 0);
	}
	return (0);
}

void	select_scene_elemt(t_minirt *win, int key_pressed)
{
	if (key_pressed == KEY_C
			|| key_pressed == KEY_L
			|| key_pressed == KEY_O
			|| key_pressed == KEY_HOME)
	{
		if (key_pressed == KEY_C)
			win->world.scene_elem = CAMERA;
		else if (key_pressed == KEY_L)
			win->world.scene_elem = LIGHT;
		else if (key_pressed == KEY_O)
			win->world.scene_elem = OBJECT;
		else if (key_pressed == KEY_HOME)
			win->world.scene_elem = NONE;
	}
	else if (win->world.scene_elem == NONE)
		printf("First select an element to move/rotate:\n\
			Use: 'c' - Camera | 'l' - Light | 'o' - Objects\n");
}


/// @brief Execute the movement of the obj.
/// @param obj Obj to be moved.
/// @param key Key mapping to move the obj.
void	execute_rotation(t_shape *obj, int key)
{
	t_matrix	*rotation;

	rotation = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(rotation);
	mtx_translation(obj->mtx_trans, &(t_point){0,0,0,1});
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

void	rotate_camera(t_minirt *win, int key)
{
	t_matrix	*rotation;
	t_camera	*camera;

	camera = &win->camera;
	rotation = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(rotation);
	mtx_translation(camera->trans, &(t_point){0,0,0,1});
	if (key == KEY_Q)
		mtx_rotation_z(rotation, -PI / 12);
	else if (key == KEY_E)
		mtx_rotation_z(rotation, PI / 12);
	else if (key == KEY_D)
		mtx_rotation_y(rotation, PI / 12);
	else if (key == KEY_A)
		mtx_rotation_y(rotation, -PI / 12);
	if (key == KEY_S)
		mtx_rotation_x(rotation, -PI / 12);
	else if (key == KEY_W)
		mtx_rotation_x(rotation, PI / 12);
	win->camera.trans = mtx_multiply(NULL, rotation, win->camera.trans);
	mtx_translation(camera->trans, &camera->center);
	clean_matrix(NULL, win->camera.inver, 0);
	win->camera.inver = mtx_inverse(win, win->camera.trans);
}


void	rotate_win(t_minirt *win, int key)
{
	(void)win;
	if (win->world.objs && win->world.scene_elem == OBJECT)
		rotate_obj_running(&win->world, key, win->world.obj_selected);
	else if (win->world.scene_elem == CAMERA)
		rotate_camera(win, key);
	redo_render(win);
}

int	handle_press_key(int key_pressed, void *param)
{
	t_minirt	*win;

	win = (t_minirt *)param;
	if (key_pressed == KEY_ESC || !win)
		close_window(win);
	else
	{	
		select_scene_elemt(win, key_pressed);
		if (win->world.scene_elem != NONE)
		{
			if (key_pressed == KEY_LEFT || key_pressed == KEY_RIGHT
				|| key_pressed == KEY_DOWN || key_pressed == KEY_UP
				|| key_pressed == KEY_PLUS || key_pressed == KEY_MINUS)
				move_win(win, key_pressed);
			else if (key_pressed == KEY_W || key_pressed == KEY_A
				|| key_pressed == KEY_S || key_pressed == KEY_D
				|| key_pressed == KEY_E || key_pressed == KEY_Q)
				rotate_win(win, key_pressed);
			else if (key_pressed == KEY_TAB && win->world.scene_elem == OBJECT)
				select_obj(win);
		}
	}
	return (0);
}

int	handle_release_key(int key_pressed, t_minirt *data)
{
	(void)data;
	(void)key_pressed;
	printf("Released\n");
	return (0);
}

void	manage_interface(t_minirt *data)
{
	mlx_hook(data->canvas.win, KeyPress, KeyPressMask, handle_press_key, data);
	mlx_hook(data->canvas.win, 17, 0L, close_window, &data);
	mlx_hook(data->canvas.win, KeyRelease, KeyReleaseMask,
		handle_release_key, data);
	mlx_loop(data->canvas.mlx);
}
