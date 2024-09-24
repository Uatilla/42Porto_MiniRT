/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                       :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:13:51 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/18 17:13:53 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	rot_cam_z(t_matrix *rotation, t_camera *camera, int key)
{
	if (key == KEY_Q)
	{
		mtx_rotation_z(rotation, PI / 12);
		camera->up = mtx_mult_tuple(rotation, &camera->up);
		camera->direct_center = mtx_mult_tuple(rotation, \
			&camera->direct_center);
	}
	else if (key == KEY_E)
	{
		mtx_rotation_z(rotation, -PI / 12);
		camera->up = mtx_mult_tuple(rotation, &camera->up);
		camera->direct_center = mtx_mult_tuple(rotation, \
			&camera->direct_center);
	}
}

void	rot_cam_y(t_matrix *rotation, t_camera *camera, int key)
{
	if (key == KEY_D)
	{
		mtx_rotation_y(rotation, PI / 12);
		camera->center = mtx_mult_tuple(rotation, &camera->center);
	}
	else if (key == KEY_A)
	{
		mtx_rotation_y(rotation, -PI / 12);
		camera->center = mtx_mult_tuple(rotation, &camera->center);
	}
}

void	rot_cam_x(t_matrix *rotation, t_camera *camera, int key)
{
	if (key == KEY_S)
	{
		mtx_rotation_x(rotation, -PI / 12);
		camera->up = mtx_mult_tuple(rotation, &camera->up);
		camera->center = mtx_mult_tuple(rotation, &camera->center);
	}
	else if (key == KEY_W)
	{
		mtx_rotation_x(rotation, PI / 12);
		camera->up = mtx_mult_tuple(rotation, &camera->up);
		camera->center = mtx_mult_tuple(rotation, &camera->center);
	}
}

void	rotate_camera(t_minirt *win, int key)
{
	t_matrix	*rotation;
	t_camera	*camera;
	t_point		angle;

	camera = &win->camera;
	rotation = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(rotation);
	rot_cam_z(rotation, camera, key);
	rot_cam_y(rotation, camera, key);
	rot_cam_x(rotation, camera, key);
	clean_matrix(win, win->camera.trans, 0);
	win->camera.trans = view_transformation(&win->camera.center, \
		&win->camera.direct_center, &camera->up);
	clean_matrix(win, rotation, 0);
	clean_matrix(NULL, win->camera.inver, 0);
	win->camera.inver = mtx_inverse(win, win->camera.trans);
}
