/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 22:31:14 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 17:28:01 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

/*
*	First will update the color of the object at the point of intersection if it
*	has a pattern.
*
*	Then will add the reflectecd color with object surface color
*
*/
t_color	shade_hit(t_comps *comps, t_world *world, t_minirt *data, \
	int8_t remainer)
{
	t_color	surface;
	t_color	reflected;
	t_color	phong;
	t_light	*light_ptr;

	set_pattern(data->first_hit, &comps->over_point);
	reflected = reflected_color(comps, data, remainer);
	surface = (t_color){0, 0, 0, 999999};
	light_ptr = world->light;
	while (light_ptr)
	{
		comps->is_shadown = is_shadowed(&data->world, light_ptr, \
				&comps->over_point);
		phong = lighting(comps, light_ptr, world);
		surface = sum_tuples(&surface, &phong);
		light_ptr = light_ptr->next;
	}
	return (sum_tuples(&surface, &reflected));
}

void	bump(t_phong *phong, t_shape *obj)
{
	if (rand() % 7 && obj->material.is_bump)
	{
		phong->diffuse.r /= 2;
		phong->diffuse.g /= 2;
		phong->diffuse.b /= 2;
	}
}
