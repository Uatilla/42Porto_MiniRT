/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:15:38 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/18 22:29:17 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	degree_to_rad(float degree)
{
	return ((degree / 180) * M_PI);
}

void	mtx_rotation_x(t_matrix *mtx, float rot_deg)
{
	mtx->mtx[1][1] = cosf(rot_deg);
	mtx->mtx[1][2] = sinf(rot_deg) * -1;
	mtx->mtx[2][1] = sinf(rot_deg);
	mtx->mtx[2][2] = cosf(rot_deg);
}

void	mtx_rotation_y(t_matrix *mtx, float rot_deg)
{
	mtx->mtx[0][0] = cosf(rot_deg);
	mtx->mtx[0][2] = sinf(rot_deg);
	mtx->mtx[2][0] = sinf(rot_deg) * -1;
	mtx->mtx[2][2] = cosf(rot_deg);
}

void	mtx_rotation_z(t_matrix *mtx, float rot_deg)
{
	mtx->mtx[0][0] = cosf(rot_deg);
	mtx->mtx[0][1] = sinf(rot_deg) * -1;
	mtx->mtx[1][0] = sinf(rot_deg);
	mtx->mtx[1][1] = cosf(rot_deg);
}
