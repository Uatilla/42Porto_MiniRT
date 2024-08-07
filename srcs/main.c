/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/07 21:56:56 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	normal_at(void *obj, t_point *point);
t_vector	reflect(t_vector *in, t_vector *normal);
t_tuple	lighting(t_attr *m, t_light *light, t_point *point, t_vector *eyev, t_vector *normalv);

// nao esquecer de setar a origem da camera(ray) e depois a direcao;
int	main(void)
{
	t_minirt	data;
	t_point		point;

	ft_memset(&data, 0, sizeof(data));
	data.ray.origin = (t_point){0,0,-5,1};
	data.light = set_light(&(t_point){0,0,0,1}, &(t_color){1,1,1,999999});
	parse_objects(SP, &data);
	point = (t_point){map_x((float)WIDTH / 2, -5, 5), map_y((float)HEIGTH / 2, -5, 5), 10, 1};
	// check_intersections(&data, &point);

	t_vector	eyev = (t_vector){0, 0, -1, 0};
	t_vector	normalv = (t_vector){0, 0, -1, 0};
	t_light		light = set_light(&(t_point){0,0,10,1}, &(t_color){1,1,1,1});

	((t_sphere *)data.objs)->attr.ambient = 0.1;
	((t_sphere *)data.objs)->attr.diffuse = 0.9;
	((t_sphere *)data.objs)->attr.specular = 0.9;
	((t_sphere *)data.objs)->attr.shininess = 200.0;
	((t_sphere *)data.objs)->attr.color = (t_color){1, 0, 0, 0};;

	t_color	result = lighting(&((t_sphere *)data.objs)->attr, &light, &point, &eyev, &normalv);

	printf("%f %f %f\n", result.r, result.g, result.b);
}

t_tuple	lighting(t_attr *m, t_light *light, t_point *point, t_vector *eyev, t_vector *normalv)
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
		diffuse = mult_tuple_scalar(&efective_color, m->diffuse);
		diffuse = mult_tuple_scalar(&diffuse, light_dot_normal);
		reflectv = negating_tuple(&lightv);
		reflectv = reflect(&reflectv, normalv);
		reflect_dot_eye = dot_product(&reflectv, eyev);
		if (reflect_dot_eye < 0)
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

t_vector	reflect(t_vector *in, t_vector *normal)
{
	float		scalar;
	t_tuple		vect;

	vect = mult_tuple_scalar(normal, 2);
	vect = mult_tuple_scalar(&vect, dot_product(in, normal));
	vect = subtrac_tuples(in, &vect);
	return (vect);
}

// int main(void)
// {
// 	t_minirt	data;
// 	t_point		point;
// 	int			x;
// 	int			y;
//
// 	ft_memset(&data, 0, sizeof(data));
// 	parse_objects(SP, &data);
// 	parse_objects(SP, &data);
// 	parse_objects(SP, &data);
// 	parse_objects(SP, &data);
// 	start_mlx(&data.canvas);
// 	data.ray.origin = (t_point){0,0,-5,1};
// 	y = -1;
// 	while (++y < HEIGTH)
// 	{
// 		x = -1;
// 		while (++x < WIDTH)
// 		{
// 			data.ray.first_hit = NULL;
// 			point = (t_point){map_x(x, -5, 5), map_y(y, -5, 5), 10, 1};
// 			check_intersections(&data, &point);
// 			if (data.ray.first_hit)
// 				write_pixel(&data.canvas, x, y, &(t_color){1,0,0,0});
// 			clear_ray_inter(&data);
// 		}
// 	}
// 	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0,0);
// 	mlx_loop(data.canvas.mlx);
// 	clear_exit(&data, 0);
// }
