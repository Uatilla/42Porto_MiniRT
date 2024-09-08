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
	return (comps);
}

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

	ft_memset(&data, 0, sizeof(data));
	data.world = *w;
	v = subtrac_tuples(&data.world.light->position, p);
	distance = magnitude(&v);
	data.ray.direction = normalize(&v);
	data.ray.origin = *p;
	check_intersections(&data);
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
	t_point	over_point;

	over_point = mult_tuple_scalar(&comps->normalv, EPSILON * 200);
	over_point = sum_tuples(&comps->point, &over_point);
	comps->is_shadown = is_shadowed(&data->world, &over_point);
	set_pattern(data->first_hit, &over_point);
	return (lighting(comps, light));
}
