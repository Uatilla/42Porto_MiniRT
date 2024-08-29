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

/*
*	adds a object node to the top of the objcts stack
*	creats a stack if is empty
*	IT PUT'S THE NEW_OBJS ON HEAD IF STACK IS NOT EMPTY.
*/
void	parse_shape(t_world *world, t_material *m, enum e_id type)
{
	t_sphere	*sphere;

	if (world->objs == NULL)
	{
		world->objs = ft_calloc(sizeof(t_sphere), 1);
		if (world->objs == NULL)
			clear_exit(NULL, errno);
		fill_sphape(world->objs, m, type);
		return ;
	}
	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (sphere == NULL)
		clear_exit(NULL, errno);
	fill_sphape(sphere, m, type);
	sphere->next = world->objs;
	world->objs = sphere;
}

//Essa funcao depende do tipo de shape que esta sendo passado
void	fill_sphape(t_sphere *sp, t_material *m, enum e_id type)
{
	t_matrix	*mtx;

	mtx = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(mtx);
	sp->type = type;
	sp->mtx_trans = mtx; //Modificar o centro do objeto
	//mtx_translation(sp->mtx_trans, &(t_point){5, 0, 0, 1});

	//Scalo o objeto (dentro da funcao escalar checo sp e aplico a regra)
	// Chamo normaliza (dentro da funcao...)
	set_materials(&sp->material, m);
}

/*
*	fisrst inplementation
*/
void	set_materials(t_material *obj, t_material *m)
{
	//Modificar a cor do objeto
	obj->color = m->color;
	obj->ambient = m->ambient;
	obj->diffuse = m->diffuse;
	obj->specular = m->specular;
	obj->shininess = m->shininess;
}
