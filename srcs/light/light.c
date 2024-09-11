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

t_color	color_at(t_minirt *data, t_ray *ray)
{
	t_color	color;
	t_comps	comps;

	check_intersections(data, ray);
	if (data->first_hit)
	{
		comps = prepare_computations(data->first_hit, ray, data);
		color = shade_hit(&comps, data->world.light, data);
	}
	else
		color = (t_color){0, 0, 0, 999999};
	clear_ray_inter(data);
	return (color);
}

/*
 * sets the values for the light object
*/
void	point_light(t_point *pos, t_color *intensity, t_world *world)
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
	t_point		local_point;
	t_vector	local_normal;
	t_vector	world_normal;
	t_matrix	*transpose;

	local_point = mtx_mult_tuple(obj->mtx_inver, point);
	local_normal = local_normal_at(obj, &local_point);
	transpose = mtx_transpose(data, obj->mtx_inver);
	world_normal = mtx_mult_tuple(transpose, &local_normal);
	world_normal.w = 0;
	clean_matrix(data, transpose, 0);
	return (normalize(&world_normal));
}

t_vector	local_normal_at(t_shape *obj, t_point *local_point)
{
	t_vector	local_normal;

	if (obj->type == SP)
		local_normal = subtrac_tuples(local_point, &(t_point){0, 0, 0, 1});
	else if (obj->type == CY)
		local_normal = normal_at_cy(local_point, obj);
	else if (obj->type == PL)
		local_normal = (t_vector){0, 1, 0, 0};
	return (local_normal);
}

t_vector	normal_at_cy(t_point *point, t_shape *obj)
{
	float	dist;

	dist = (point->x * point->x) + (point->z * point->z);
	if (dist < 1 && point->y >= obj->material.max - EPSILON)
		return ((t_vector){0, 1, 0, 0});
	else if (dist < 1 && point->y <= obj->material.min + EPSILON)
		return ((t_vector){0, -1, 0, 0});
	return ((t_vector){point->x, 0, point->z, 0});
}

/*
*	returns the reflected vector from in at a normal vector
*/
t_vector	reflect(t_vector *in, t_vector *normal)
{
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
t_color	lighting(t_comps *comps, t_light *light)
{
	t_color			color;
	t_phong			phong;
	float			light_normal_dot;
	float			ref_dot_eye;
	float			factor;

	color = color_multiply(&comps->obj->material.color, &light->intensity);
	comps->lightv = subtrac_tuples(&light->position, &comps->point);
	comps->lightv = normalize(&comps->lightv);
	phong.ambient = mult_tuple_scalar(&color, comps->obj->material.ambient);
	light_normal_dot = dot_product(&comps->lightv, &comps->normalv);
	if (light_normal_dot < 0 || comps->is_shadown)
		light_is_behind_obj(&phong.diffuse, &phong.spec);
	else
	{
		phong.diffuse = mult_tuple_scalar(&color,
							comps->obj->material.diffuse * light_normal_dot);
		comps->reflectv = negating_tuple(&comps->lightv);
		comps->reflectv = reflect(&comps->reflectv, &comps->normalv);
		ref_dot_eye = dot_product(&comps->reflectv, &comps->eyev);
		if (ref_dot_eye <= 0)
			phong.spec = (t_color){0, 0, 0, 999999};
		else
			phong.spec = specular(&comps->obj->material, light, ref_dot_eye);
	}
	return (add_color3(&phong.ambient, &phong.diffuse, &phong.spec));
}
