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
	world = &mrt->world;
	mrt->world.n_objs++;
	if (world->objs == NULL)
	{
		world->objs = ft_calloc(sizeof(t_shape), 1);
		if (world->objs == NULL)
			clear_exit(NULL, errno);
		world->objs->id = mrt->world.n_objs;
		fill_shape(world->objs, type, line, world->ambient_ratio);
		return ;
	}
	shape = ft_calloc(sizeof(t_shape), 1);
	if (shape == NULL)
		clear_exit(NULL, errno);
	shape->id = mrt->world.n_objs;
	fill_shape(shape, type, line, world->ambient_ratio);
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
		diam = (2 * ft_atof(line[2])) / 100;
	else
		diam = (2 * ft_atof(line[3])) / 100;
	mtx_scaling(mtx, &(t_point){diam, diam, diam, 1});
	sp->mtx_trans = mtx_multiply(NULL, mtx, sp->mtx_trans);
}

/// @brief Find the right angle to rotate in each axis.
/// @param reference Normalized vector reference for each axis.
/// @param p Normalized vector from the input.
/// @return The angle found for that axis.
float	find_angle(t_point	reference, t_point p)
{
	float	dot_p;
	float	mag_ref;
	float	mag_p;

	dot_p = (reference.x * p.x) + (reference.y * p.y) + (reference.z * p.z);
	mag_ref = sqrtf((reference.x * reference.x) + (reference.y * reference.y)
			+ (reference.z * reference.z));
	mag_p = sqrtf((p.x * p.x) + (p.y * p.y) + (p.z * p.z));
	return (acos(dot_p / (mag_ref * mag_p)));
}

/// @brief Effectively execute the rotation of the object.
/// @param sp Shape to be rotated.
void	exec_rotation(t_shape *sp)
{
	t_matrix	*cy_rot_x;
	t_matrix	*cy_rot_y;
	t_matrix	*cy_rot_z;

	cy_rot_x = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(cy_rot_x);
	mtx_rotation_x(cy_rot_x, PI / 4);
	mtx_rotation_x(cy_rot_x, sp->angle.x);
	sp->mtx_trans = mtx_multiply(NULL, cy_rot_x, sp->mtx_trans);
	cy_rot_y = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(cy_rot_y);
	mtx_rotation_y(cy_rot_y, sp->angle.y);
	sp->mtx_trans = mtx_multiply(NULL, cy_rot_y, sp->mtx_trans);
	cy_rot_z = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(cy_rot_z);
	mtx_rotation_z(cy_rot_z, sp->angle.z);
	sp->mtx_trans = mtx_multiply(NULL, cy_rot_z, sp->mtx_trans);
}

/// @brief Rotate each object if (PL or CY).
/// @param sp Shape to be rotate.
/// @param  type NOT IN USE.
/// @param line Line of the input to check the normalized vector.
void	rotate_obj(t_shape *sp, enum e_id type, char **line)
{
	t_point	norm_vect;

	(void)type;
	norm_vect = get_tuple(line[2], 1);
	sp->angle.x = find_angle((t_point){1, 0, 0, 1}, norm_vect);
	sp->angle.y = find_angle((t_point){0, 1, 0, 1}, norm_vect);
	sp->angle.z = find_angle((t_point){0, 0, 1, 1}, norm_vect);
	sp->angle.w = 2;
	exec_rotation(sp);
}

/// @brief Set the obj parameter (position, scale and so on).
/// @param sp Shape to be filled.
/// @param type Type of the object identified.
/// @param line Line from the scene file to be used.
void	fill_shape(t_sphere *sp, enum e_id type, char **line, float amb_ratio)
{
	t_matrix	*mtx;
	t_material	m1;
	t_point		obj_center;

	sp->amb_ratio = amb_ratio;
	obj_center = get_tuple(line[1], 1);
	sp->center = obj_center;
	mtx = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(mtx);
	sp->mtx_trans = mtx;
	sp->type = type;
	m1 = parse_material(line, type);
	if (type == PL || type == CY || type == CONE)
		rotate_obj(sp, type, line);
	if (type == SP || type == CY || type == CONE)
		scale_obj(sp, type, line);
	mtx_translation(sp->mtx_trans, &obj_center);
	set_materials(sp, &m1, line, type);
	sp->mtx_inver = mtx_inverse(NULL, sp->mtx_trans);
}

int	count_words(char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		continue ;
	return (i);
}

/// @brief Set the color for the object.
/// @param obj_color tuple from the object structure.
/// @param line Scene line to be used.
/// @param type Type of the object.
/// @param color_type 'P' for Primary or 'S' for Secondary(texture).
void	set_color(t_color *obj_color, char **line,
	enum e_id type, char color_type)
{
	if (color_type == 'P')
	{
		if (type == SP || type == PL)
			fill_tuple(obj_color, line[3], 999999);
		else if (type == CY || type == CONE)
			fill_tuple(obj_color, line[5], 999999);
	}
	else if (color_type == 'S')
	{
		if ((type == SP || type == PL) && count_words(line) == 7)
			fill_tuple(obj_color, line[5], 999999);
		else if ((type == CY || type == CONE) && count_words(line) == 9)
			fill_tuple(obj_color, line[7], 999999);
	}
	obj_color->r = obj_color->r / 255;
	obj_color->g = obj_color->g / 255;
	obj_color->b = obj_color->b / 255;
}

void	set_cyl_specs(t_point *center, t_material *obj, char **line)
{
	float	height;

	height = 2 * (ft_atof(line[4]) / 100);
	obj->min = center->y - (height / 2);
	obj->max = center->y + (height / 2);
	obj->closed = true;
}

void	attribute_pattern(enum e_id type, t_material *obj_mat, char **line)
{
	char		*pattern;
	enum e_p	patt_type;

	set_color(&obj_mat->color_sec, line, type, 'S');
	if (type == PL || type == SP)
		pattern = line[6];
	else if (type == CY || type == CONE)
		pattern = line[8];
	if (!ft_strcmp(pattern, "PC"))
		patt_type = PC;
	else if (!ft_strcmp(pattern, "GR"))
		patt_type = GR;
	else if (!ft_strcmp(pattern, "RNG"))
		patt_type = RNG;
	else if (!ft_strcmp(pattern, "CHK"))
		patt_type = CHK;
	obj_mat->pattern = stripe_pattern(&obj_mat->color,
			&obj_mat->color_sec, patt_type);
	obj_mat->pattern.inver = mtx_inverse(NULL, obj_mat->pattern.trans);
}

/// @brief Set the obj material parameters
/// @param obj Object to have its materials defined.
/// @param m Standard material parameters.
/// @param line Scene line to be used.
/// @param type Type of the object.
void	set_materials(t_shape *sp, t_material *m,
		char **line, enum e_id type)
{
	t_material	*obj_mat;

	obj_mat = &sp->material;
	set_color(&obj_mat->color, line, type, 'P');
	obj_mat->ambient = m->ambient;
	obj_mat->diffuse = m->diffuse;
	obj_mat->specular = m->specular;
	obj_mat->shininess = m->shininess;
	obj_mat->pattern.has = false;
	if (type == CY || type == CONE)
		set_cyl_specs(&sp->center, obj_mat, line);
	if (((type == PL || type == SP) && count_words(line) == 7)
		|| ((type == CY || type == CONE) && count_words(line) == 9))
		attribute_pattern(type, obj_mat, line);
}
