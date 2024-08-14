/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 22:31:14 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/08 22:35:12 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
*	fills the light strcut with the direction, the normal, the reflect vector
*	and the eye vector
*/
void	light_vec(t_ray *ray, t_light *light)
{
	light->dir = subtrac_tuples(&light->position, &ray->first_hit->point);
	light->dir = normalize(&light->dir);
	light->normalv = normal_at(ray->first_hit->obj, &ray->first_hit->point);
	light->reflect = negating_tuple(&light->dir);
	light->reflect = reflect(&light->reflect, &light->normalv);
	light->eyev = negating_tuple(&ray->direction);
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