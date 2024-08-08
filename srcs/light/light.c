/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:48:55 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/07 17:49:42 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
 * sets the values for the light object
*/
t_light	set_light(t_point *position, t_color *intensity)
{
	return ((t_light){*position,*intensity});
}

/*
 * In the case of a sphere the normal vector will be the normalize distance
 * of point (assuming point is the coordenates of a point in the circunference)
 * and its center.
 *
* care to not have the point has the same cordenates as the obj.center
* the result will be nan in that case
*/
t_vector	normal_at(void *obj, t_point *point)
{
	t_vector	vec;

	if (((t_sphere *)obj)->type == SP)
	{
		vec = subtrac_tuples(point, &((t_sphere *)obj)->center);
		vec = normalize(&vec);
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

t_tuple	lighting(t_material *m, t_light *light, t_point *point, t_vector *eyev, t_vector *normalv)
{
	t_color		efective_color;
	t_vector	lightv;
	t_tuple		ambient;
	float		light_dot_normal;
	t_tuple			diffuse;
	t_tuple 		specular;
	t_vector		reflectv;
	float			reflect_dot_eye;
	float			factor;

	efective_color = color_multiply(&m->color, &light->intensity);
	lightv = subtrac_tuples(&light->position, point);
	lightv = normalize(&lightv);
	ambient = mult_tuple_scalar(&efective_color, m->ambient);
	light_dot_normal = dot_product(&lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = (t_tuple){0,0,0,0};
		specular = (t_tuple){0,0,0,0};
	}
	else
	{
		diffuse = mult_tuple_scalar(&efective_color, m->diffuse * light_dot_normal);
		reflectv = negating_tuple(&lightv);
		reflectv = reflect(&reflectv, normalv);
		reflect_dot_eye = dot_product(&reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular = (t_tuple){0,0,0,0};
		else
		{
			factor = powf(reflect_dot_eye, m->shininess);
			specular = mult_tuple_scalar(&light->intensity, m->specular * factor);
		}
	}
	t_tuple add = sum_tuples(&ambient, &diffuse);
	add = sum_tuples(&add, &specular);
	return (add);
}
