/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:48:55 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 17:31:27 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
/*
 *	The call to intersections will check if the ray intercets a object
 *		If it does will prepare the compuations then the shade_hit will return
 *		the color of the pixel
 */
t_color	color_at(t_minirt *data, t_ray *ray, int8_t remainer)
{
	t_color	color;
	t_comps	comps;

	intersections(data, ray);
	if (data->first_hit)
	{
		comps = prepare_computations(data->first_hit, ray, data);
		color = shade_hit(&comps, &data->world, data, remainer);
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
		world->light->next = NULL;
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
t_color	lighting(t_comps *comps, t_light *light, t_world *world)
{
	t_color			color;
	t_phong			phong;
	float			light_normal_dot;

	color = color_multiply(&comps->obj->material.color, &world->ambient_light);
	comps->lightv = subtrac_tuples(&light->position, &comps->point);
	comps->lightv = normalize(&comps->lightv);
	phong.ambient = mult_tuple_scalar(&color, comps->obj->material.ambient);
	light_normal_dot = dot_product(&comps->lightv, &comps->normalv);
	if (light_normal_dot < 0 || comps->is_shadown)
		light_is_behind_obj(&phong.diffuse, &phong.spec);
	else
	{
		color = color_multiply(&color, &light->intensity);
		phong.diffuse = mult_tuple_scalar(&color,
				comps->obj->material.diffuse * light_normal_dot);
		bump(&phong, comps->obj);
		comps->reflectv = negating_tuple(&comps->lightv);
		comps->reflectv = reflect(&comps->reflectv, &comps->normalv);
		get_specular(comps, light, &phong);
	}
	return (add_color3(&phong.ambient, &phong.diffuse, &phong.spec));
}

void	get_specular(t_comps *comps, t_light *light, t_phong *phong)
{
	float			ref_dot_eye;

	ref_dot_eye = dot_product(&comps->reflectv, &comps->eyev);
	if (ref_dot_eye <= 0)
		phong->spec = (t_color){0, 0, 0, 999999};
	else
		phong->spec = specular(&comps->obj->material, light, ref_dot_eye);
}
