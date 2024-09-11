/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:04:30 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/23 19:07:49 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	parse_shape(t_minirt *mrt, enum e_id type, char **line)
{
	t_shape	*shape;
	t_world	*world;
	(void)line;

	printf("OI\n");

	world = &mrt->world;
	mrt->world.n_objs++;
	if (world->objs == NULL)
	{
		world->objs = ft_calloc(sizeof(t_shape), 1);
		if (world->objs == NULL)
			clear_exit(NULL, errno);
		world->objs->id = mrt->world.n_objs;
		fill_sphape(world->objs, type, line);
		return ;
	}
	shape = ft_calloc(sizeof(t_shape), 1);
	if (shape == NULL)
		clear_exit(NULL, errno);
	shape->id = mrt->world.n_objs;
	fill_sphape(shape, type, line);
	shape->next = world->objs;
	world->objs = shape;
}

/// @brief Scales SP or CY from the scene file.
/// @param sp Shape obj.
/// @param type Type of the obj.
/// @param line Line to be used to scale from the scene file.
void	scale_obj(t_shape *sp, enum e_id type, char **line)
{
	float		diam;
	t_matrix	*mtx;

	mtx = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(mtx);
	if (type == SP)
	{
		diam = (2 * ft_atof(line[2])) / 100;
		mtx_scaling(mtx, &(t_point){diam, diam, diam, 1});
		sp->mtx_trans = mtx_multiply(NULL, mtx, sp->mtx_trans);
	}
	else
		printf("Scaling Cylinder (TO BE DEFINED)\n");
		/*mrt->input.cylinder.cy_diam = ft_atof(line[3]);
	mrt->input.cylinder.cy_height = ft_atof(line[4]);*/
}

void	normalize_obj(t_shape *sp, enum e_id type, char **line)
{
	t_matrix	*mtx;
	(void)type;
	(void)line;
	(void)sp;


	mtx = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(mtx);
	mtx_rotation_z(mtx, degree_to_rad(45));
	printf("After Rotation X\n");
	mtx_print(mtx);

	t_tuple tup_res;
	t_tuple p;

	p.x = 0;
	p.y = 1;
	p.z = 0;
	p.w = 1;
	printf("\nP -> X:%f Y:%f Z:%f W:%f\n", p.x, p.y, p.z, p.w);
	tup_res = mtx_mult_tuple(mtx,&p);
	printf("Tup_Res -> X:%f Y:%f Z:%f W:%f\n", tup_res.x, tup_res.y, tup_res.z, tup_res.w);
	sp->mtx_trans = mtx_multiply(NULL, mtx, sp->mtx_trans);

	/*if (type == PL)
		printf("Normalize: %s\n", line[2]);*/



		//fill_tuple(&mrt->input.plane.pl_norm_vect, line[2], 0);
	//else
		//fill_tuple(&mrt->input.cylinder.cy_norm_vect, line[2], 0);
}

/// @brief Set the obj parameter (position, scale and so on).
/// @param sp Shape to be filled.
/// @param type Type of the object identified.
/// @param line Line from the scene file to be used.
void	fill_sphape(t_sphere *sp, enum e_id type, char **line)
{
	t_matrix	*mtx;
	t_material	m1;
	t_point		obj_center;

	obj_center = get_tuple(line[1], 1);
	sp->center = obj_center;
	mtx = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(mtx);
	sp->type = type;
	m1 = parse_material(line, type);
	sp->mtx_trans = mtx;
	if (type == PL || type == CY)
		normalize_obj(sp, type, line);
	if (type == SP || type == CY)
		scale_obj(sp, type, line);
		
	mtx_translation(sp->mtx_trans, &obj_center);
	set_materials(&sp->material, &m1, line, type);
	sp->mtx_inver = mtx_inverse(NULL, sp->mtx_trans);
}


/// @brief Set the color for the object.
/// @param obj_color tuple from the object structure.
/// @param line Scene line to be used.
/// @param type Type of the object.
void	set_color(t_color *obj_color, char **line, enum e_id type)
{
	if (type == SP || type == PL)
		fill_tuple(obj_color, line[3], 999999);
	else if (type == CY)
		fill_tuple(obj_color, line[5], 999999);
	obj_color->r = obj_color->r / 255;
	obj_color->g = obj_color->g / 255;
	obj_color->b = obj_color->b / 255;
}

/// @brief Set the obj material parameters
/// @param obj Object to have its materials defined.
/// @param m Standard material parameters.
/// @param line Scene line to be used.
/// @param type Type of the object.
void	set_materials(t_material *obj, t_material *m,
		char **line, enum e_id type)
{
	set_color(&obj->color, line, type);
	obj->ambient = m->ambient;
	obj->diffuse = m->diffuse;
	obj->specular = m->specular;
	obj->shininess = m->shininess;
	obj->pattern = m->pattern;
}
