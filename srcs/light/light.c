/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:48:55 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/19 16:58:50 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	color_at(t_minirt *data)
{
	t_color	color;

	check_intersections(data);
	light_vec(&data->ray, data->world.light, data);
	color = lighting(data->first_hit, data->world.light);
	return (color);
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
t_vector	normal_at(void *obj, t_point *point, t_minirt *data)
{
	t_vector	vec;
	t_matrix	*transpose;

	if (((t_sphere *)obj)->type == SP)
	{
		vec = mtx_mult_tuple(((t_sphere *)obj)->mtx_inver, point);
		vec = subtrac_tuples(&vec, &(t_point){0, 0, 0, 1});
		transpose = mtx_transpose(data, ((t_sphere *)obj)->mtx_inver);
		vec = mtx_mult_tuple(transpose, &vec);
		vec.w = 0;
		vec = normalize(&vec);
		clean_matrix(data, transpose, 0);
	}
	else if (((t_cylinder *)obj)->type == CY)
	{
		vec.x = point->x;
		vec.y = 0;
		vec.z = point->z;
	}
	return (vec);
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

	color = color_multiply(&((t_sphere *)inter->obj)->material.color,
			&light->intensity);
	phong.ambient = mult_tuple_scalar(&color,
			((t_sphere *)inter->obj)->material.ambient);
	light_normal_dot = dot_product(&light->dir, &light->normalv);
	if (light_normal_dot < 0)
		light_is_behind_obj(&phong.diffuse, &phong.spec);
	else
	{
		phong.diffuse = mult_tuple_scalar(&color,
				((t_sphere *)inter->obj)->material.diffuse * light_normal_dot);
		ref_dot_eye = dot_product(&light->reflect, &light->eyev);
		if (ref_dot_eye <= 0)
			phong.spec = (t_color){0, 0, 0, 0};
		else
			phong.spec = specular(&((t_sphere *)inter->obj)->material,
					light, ref_dot_eye);
	}
	return (add_color3(&phong.ambient, &phong.diffuse, &phong.spec));
}
