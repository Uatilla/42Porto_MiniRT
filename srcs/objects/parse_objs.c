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

/// @brief Set cylinder or cone specs (height and width).
/// @param center Center of the object.
/// @param obj Object on stack.
/// @param line Line of the input.
void	set_cyl_specs(t_point *center, t_material *obj, char **line)
{
	float	height;

	height = 2 * (ft_atof(line[4]) / 100);
	obj->min = center->y - (height / 2);
	obj->max = center->y + (height / 2);
	obj->closed = true;
}
