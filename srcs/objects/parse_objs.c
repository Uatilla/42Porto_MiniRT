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

/*
*	adds a object node to the top of the objcts stack
*	creats a stack if is empty
*/
void	parse_sphere2(t_world *world, t_material *m)
{
	t_sphere	*sphere;

	if (world->sphere == NULL)
	{
		world->sphere = ft_calloc(sizeof(t_sphere), 1);
		if (world->sphere == NULL)
			clear_exit(NULL, errno);
		fill_sphere(world->sphere, m);
		return ;
	}
	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (sphere == NULL)
		clear_exit(NULL, errno);
	fill_sphere(sphere, m);
	//Novo objeto recebe o antigo?
	sphere->next = world->sphere;
	world->sphere = sphere;
}

void	fill_sphere(t_sphere *sp, t_material *m)
{
	t_matrix	*mtx;

	mtx = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(mtx);
	sp->type = SP;
	sp->mtx_trans = mtx;
	set_materials(&sp->material, m);
}

/*
*	fisrst inplementation
*/
void	set_materials(t_material *obj, t_material *m)
{
	obj->color = m->color;
	obj->ambient = m->ambient;
	obj->diffuse = m->diffuse;
	obj->specular = m->specular;
	obj->shininess = m->shininess;
}
