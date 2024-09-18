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
