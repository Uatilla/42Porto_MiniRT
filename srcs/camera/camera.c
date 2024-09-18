/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:34:32 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 17:20:18 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
*	This function returns the ray, set from the camera origim
*	throught each given pixel
*/
t_ray	ray_for_pixel(t_camera *camera, size_t px, size_t py)
{
	t_ray	ray;
	t_point	pixel;
	t_rfp	rpf;

	rpf.xoffset = (px + 0.5) * camera->pixel_size;
	rpf.yoffset = (py + 0.5) * camera->pixel_size;
	rpf.w_x = camera->half_width - rpf.xoffset;
	rpf.w_y = camera->half_height - rpf.yoffset;
	pixel = mtx_mult_tuple(camera->inver, &(t_point){rpf.w_x, rpf.w_y, -1, 1});
	ray.origin = mtx_mult_tuple(camera->inver, &(t_point){0, 0, 0, 1});
	ray.direction = subtrac_tuples(&pixel, &ray.origin);
	ray.direction = normalize(&ray.direction);
	return (ray);
}

t_camera	camera_construct(size_t hsize, size_t vsize, float fov)
{
	t_camera	camera;
	float		half_view;
	float		aspect;

	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.fov = fov;
	half_view = tan(fov / 2);
	aspect = (float)hsize / (float)vsize;
	if (aspect >= 1)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect;
	}
	else
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2) / hsize;
	return (camera);
}
