/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:04:30 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/19 16:57:07 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	parse_objects(enum e_identifyer type, t_world *world)
{
	if (type == SP)
		parse_sphere(world);
}

/*
*	adds a object node to the top of the objcts stack
*	creats a stack if is empty
*/
void	parse_sphere(t_world *world)
{
	t_sphere	*sphere;

	if (world->sphere == NULL)
	{
		world->sphere = ft_calloc(sizeof(t_sphere), 1);
		if (world->sphere == NULL)
			clear_exit(NULL, errno);
		fill_sphere(world->sphere);
		return ;
	}
	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (sphere == NULL)
		clear_exit(NULL, errno);
	fill_sphere(sphere);
	sphere->next = world->sphere;
	world->sphere = sphere;
}

void	fill_sphere(t_sphere *sp)
{
	t_matrix	*mtx;

	mtx = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(mtx);
	sp->type = SP;
	sp->mtx_trans = mtx;
	set_materials(&sp->material);
}

/*
*	fisrst inplementation
*/
void	set_materials(t_material *material)
{
	material->color = (t_color){0.8, 1.0, 0.6, 999999};
	material->ambient = 0.1;
	material->diffuse = 0.7;
	material->specular = 0.2;
	material->shininess = 100.0;
}
