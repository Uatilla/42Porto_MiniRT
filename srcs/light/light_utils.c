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

/*
*	fills the light strcut with the direction, the normal, the reflect vector
*	and the eye vector
*/
void	light_vec(t_ray *ray, t_light *light, t_minirt *data)
{
	t_point	over_point;

	light->dir = subtrac_tuples(&light->position, &data->first_hit->point);
	light->dir = normalize(&light->dir);
	light->eyev = negating_tuple(&ray->direction);
	light->normalv = normal_at(data->first_hit->obj, &data->first_hit->point, data);
	if (dot_product(&light->normalv, &light->eyev) < 0)
		light->normalv = negating_tuple(&light->normalv);
	light->reflect = negating_tuple(&light->dir);
	light->reflect = reflect(&light->reflect, &light->normalv);
	over_point = mult_tuple_scalar(&light->normalv, EPSILON * 100);
	over_point = sum_tuples(&data->first_hit->point, &over_point);
	light->is_shadown = is_shadowed(&data->world, &over_point);
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
	*diffuse = (t_color){0, 0, 0, 0};
	*specular = (t_color){0, 0, 0, 0};
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

