/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:21:18 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/18 17:21:20 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	move_cam_x(t_camera *camera, int key)
{
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
}

void	move_cam_y(t_camera *camera, int key)
{
	if (key == KEY_DOWN)
	{
		camera->center.y = camera->center.y - 1;
		camera->direct_center.y = camera->direct_center.y - 1;
	}
	else if (key == KEY_UP)
	{
		camera->center.y = camera->center.y + 1;
		camera->direct_center.y = camera->direct_center.y + 1;
	}
}

void	move_cam_z(t_camera *camera, int key)
{
	if (key == KEY_PLUS)
	{
		camera->center.z = camera->center.z + 1;
		camera->direct_center.z = camera->direct_center.z + 1;
	}
	else if (key == KEY_MINUS)
	{
		camera->center.z = camera->center.z - 1;
		camera->direct_center.z = camera->direct_center.z - 1;
	}
}

/// @brief Move the camera.
/// @param win Main structure of the program.
/// @param key Key pressed by the user.
void	move_camera(t_minirt *win, int key)
{
	t_camera	*camera;

	camera = &win->camera;
	move_cam_x(camera, key);
	move_cam_y(camera, key);
	move_cam_z(camera, key);
	clean_matrix(NULL, win->camera.trans, 0);
	win->camera.trans = view_transformation(&win->camera.center, \
		&win->camera.direct_center, &camera->up);
	clean_matrix(NULL, win->camera.inver, 0);
	win->camera.inver = mtx_inverse(win, win->camera.trans);
}
