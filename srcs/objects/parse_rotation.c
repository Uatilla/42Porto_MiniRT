/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:11:27 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/18 20:11:29 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_matrix	*execute_rot_z(t_vector *orient, t_matrix *rotation)
{
	t_matrix	*rot_z;

	rot_z = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(rot_z);
	mtx_rotation_x(rot_z, orient->z * M_PI / 2);
	if (orient->x || orient->y)
		rotation = mtx_multiply(NULL, rotation, rot_z);
	else
	{
		clean_matrix(NULL, rotation, 0);
		rotation = rot_z;
	}
	return (rotation);
}

t_matrix	*execute_rot_y(t_vector *orient, t_matrix *rotation)
{
	t_matrix	*rot_y;

	rot_y = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(rot_y);
	mtx_rotation_y(rot_y, orient->y * M_PI / 2);
	if (orient->x)
		rotation = mtx_multiply(NULL, rotation, rot_y);
	else
	{
		clean_matrix(NULL, rotation, 0);
		rotation = rot_y;
	}
	return (rotation);
}

/// @brief Rotate each object if (PL or CY).
/// @param sp Shape to be rotate.
/// @param  type NOT IN USE.
/// @param line Line of the input to check the normalized vector.
void	rotate_obj(t_shape *sp, enum e_id type, char **line)
{
	t_vector	orient;
	t_matrix	*rotation;

	(void)type;
	orient = get_tuple(line[2], 1);
	rotation = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(rotation);
	if (orient.x)
		mtx_rotation_z(rotation, orient.x * M_PI / 2);
	if (orient.y)
		rotation = execute_rot_y(&orient, rotation);
	if (orient.z)
		rotation = execute_rot_z(&orient, rotation);
	sp->mtx_trans = mtx_multiply(NULL, sp->mtx_trans, rotation);
}
