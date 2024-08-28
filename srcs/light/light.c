/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:48:55 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/23 19:09:39 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	color_at(t_minirt *data, int x, int y)
{
	t_color	color;

	check_intersections(data);
	if (data->first_hit)
	{
		light_vec(&data->ray, data->world.light, data);
		color = lighting(data->first_hit, data->world.light);
		write_pixel(&data->canvas, x, y, &color);
	}
	clear_ray_inter(data);
}

/*
 * sets the values for the light object
*/
void	set_light(t_point *pos, t_color *intensity, t_world *world)
{
	t_light	*light;

	if (world->light == NULL)
	{
		world->light = ft_calloc(sizeof(*world->light), 1);
		if (world->light == NULL)
			exit (errno);
		world->light->position = *pos;
		world->light->intensity = *intensity;
		return ;
	}
	light = ft_calloc(sizeof(*light), 1);
	if (light == NULL)
		exit(errno);
	light->position = *pos;
	light->intensity = *intensity;
	light->next = world->light;
	world->light = light;
}

/*
 * In the case of a sphere the normal vector will be the normalize distance
 * of point (assuming point is the coordenates of a point in the circunference)
 * and its center.
 *
* care to not have the point has the same cordenates as the obj.center
* the result will be nan in that case
*
*/
t_vector	normal_at(t_shape *obj, t_point *point, t_minirt *data)
{
	t_vector	local_normal;
	t_vector	world_normal;
	t_matrix	*transpose;

	if (obj->type == SP)
	{
		local_normal = mtx_mult_tuple(obj->mtx_inver, point);
		local_normal = subtrac_tuples(&local_normal, &(t_point){0, 0, 0, 1});
		transpose = mtx_transpose(data, obj->mtx_inver);
		world_normal = mtx_mult_tuple(transpose, &local_normal);
		world_normal.w = 0;
		world_normal = normalize(&world_normal);
		clean_matrix(data, transpose, 0);
	}
	else if (obj->type == PL)
		return ((t_vector){0, 1, 0, 0});
	// else if (obj->type == CY)
	// {
	// 	vec.x = point->x;
	// 	vec.y = 0;
	// 	vec.z = point->z;
	// }
	return (world_normal);
}

/*
*	returns the reflected vector from in at a normal vector
*/
t_vector	reflect(t_vector *in, t_vector *normal)
{
	float		scalar;
	t_tuple		vect;

	vect = mult_tuple_scalar(normal, 2);
	vect = mult_tuple_scalar(&vect, dot_product(in, normal));
	vect = subtrac_tuples(in, &vect);
	return (vect);
}

/*
*	does the phong reflection algorithm, returns the final collor
*	acording to the relation with the light reflection and the camera
*/
t_color	lighting(t_intersections *inter, t_light *light)
{
	t_color			color;
	t_phong			phong;
	float			light_normal_dot;
	float			ref_dot_eye;
	float			factor;

	color = color_multiply(&inter->obj->material.color, &light->intensity);
	phong.ambient = mult_tuple_scalar(&color, inter->obj->material.ambient);
	light_normal_dot = dot_product(&light->dir, &light->normalv);
	if (light_normal_dot < 0 || light->is_shadown)
		light_is_behind_obj(&phong.diffuse, &phong.spec);
	else
	{
		phong.diffuse = mult_tuple_scalar(&color,
							inter->obj->material.diffuse * light_normal_dot);
		ref_dot_eye = dot_product(&light->reflect, &light->eyev);
		if (ref_dot_eye <= 0)
			phong.spec = (t_color){0, 0, 0, 0};
		else
			phong.spec = specular(&inter->obj->material, light, ref_dot_eye);
	}
	return (add_color3(&phong.ambient, &phong.diffuse, &phong.spec));
}
