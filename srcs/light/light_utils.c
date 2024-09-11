/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 22:31:14 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/22 16:45:08 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_comps	prepare_computations(t_intersections *i, t_ray *ray, t_minirt *data)
{
	t_comps	comps;
	t_point	over_point;

	comps.t = i->hit;
	comps.obj = i->obj;
	comps.point = i->point;
	comps.eyev = negating_tuple(&ray->direction);
	comps.normalv = normal_at(comps.obj, &comps.point, data);
	if (dot_product(&comps.normalv, &comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negating_tuple(&comps.normalv);
	}
	else
		comps.inside = false;
	comps.over_point = mult_tuple_scalar(&comps.normalv, EPSILON * 200);
	comps.over_point = sum_tuples(&comps.point, &comps.over_point);
	// comps.reflectv = reflect(&ray->direction, &comps.normalv);
	return (comps);
}

// t_color	reflected_color(t_comps *comps, t_minirt *data, int8_t remaining)
// {
// 	t_color	color;
// 	t_ray	reflected_ray;
//
// 	if (comps->obj->material.reflective == 0 || remaining == 0)
// 		return ((t_color){0, 0, 0, 999999});
// 	reflected_ray.origin = comps->over_point;
// 	reflected_ray.direction = comps->reflectv;
// 	// color = color_at(data, &reflected_ray);
// 	color = mult_tuple_scalar(&color, comps->obj->material.reflective);
// 	return (color);
// }

/*
 * adds the ambient the diffuse and the specular
*/
t_color	add_color3(t_color *ambient, t_color *diffuse, t_color *specular)
{
	t_color	add;

	add = sum_tuples(ambient, diffuse);
	add = sum_tuples(&add, specular);
	return (add);
}

/*
 * sets the diffuse and the specular values to 0 if the light is behint the obj
*/
void	light_is_behind_obj(t_color *diffuse, t_color *specular)
{
	*diffuse = (t_color){0, 0, 0, 999999};
	*specular = (t_color){0, 0, 0, 999999};
}

/*
 * sets the specular value
*/
t_color	specular(t_material *material, t_light *light, float refl_dot_eye)
{
	float	factor;

	factor = powf(refl_dot_eye, material->shininess);
	return (mult_tuple_scalar(&light->intensity, material->specular * factor));
}

bool	is_shadowed(t_world *w, t_point *p)
{
	t_minirt	data;
	t_vector	v;
	float		distance;
	t_ray		ray;

	ft_memset(&data, 0, sizeof(data));
	data.world = *w;
	v = subtrac_tuples(&data.world.light->position, p);
	distance = magnitude(&v);
	ray.direction = normalize(&v);
	ray.origin = *p;
	check_intersections(&data, &ray);
	first_hit(&data);
	if (data.first_hit && distance > data.first_hit->hit)
	{
		clear_ray_inter(&data);
		return (true);
	}
	clear_ray_inter(&data);
	return (false);
}

t_color	shade_hit(t_comps *comps, t_light *light, t_minirt *data)
{
	t_color	surface;
	t_color	reflected;

	set_pattern(data->first_hit, &comps->over_point);
	comps->is_shadown = is_shadowed(&data->world, &comps->over_point);
	return (lighting(comps, light));
	// surface = lighting(comps, light);
	// reflected = reflected_color(comps, data, remaining);
	// return (sum_tuples(&surface, &reflected));
}
