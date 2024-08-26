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

void	fill_sphape(t_sphere *sp, t_material *m, enum e_id type)
{
	t_matrix	*mtx;

	mtx = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(mtx);
	sp->type = type;
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

void	parse_line(t_minirt *mrt, char **line)
{
	(void)mrt;
	if (line[0])
	{
		if (!ft_strcmp(line[0], "A"))
			parse_ambient(mrt, line);
		else if (!ft_strcmp(line[0], "C"))
			parse_camera(mrt, line);
		else if (!ft_strcmp(line[0], "L"))
			parse_light(mrt, line);
		else if (!ft_strcmp(line[0], "sp"))
			printf("sp\n");
		else if (!ft_strcmp(line[0], "pl"))
			printf("pl\n");
		else if (!ft_strcmp(line[0], "cy"))
			printf("cy\n");
	}
	free_split(line);
}

void	set_scene(t_minirt *mrt, char *file)
{
	char		*line;
	char		*line_trimmed;
	char		**line_cleaned;
	int			fd;

	(void)mrt;
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
	{
		ft_error(NULL, "ERROR: Failed to open the\
				scene file, try another one.\n", 0);
		clear_exit(NULL, 1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_replace(line, '\t', ' ');
		line_trimmed = ft_strtrim(line, "\n");
		free(line);
		line_cleaned = ft_split(line_trimmed, ' ');
		free(line_trimmed);
		parse_line(mrt, line_cleaned);
	}
	close (fd);
}

/// @brief Takes a string and puts its values into a tuple.
/// @param tuple Where do you want to have the str elements.
/// @param str_tuple Source of the tuple elements.
/// @param w Content of the W pos in the tuple.
void	get_tuple(t_tuple *tuple, char *str_tuple, int w)
{
	int	elemnt;
	char **rgb_elemnts;
	float	*ptr;

	ptr =(float *)tuple;
	elemnt = -1;
	rgb_elemnts = ft_split(str_tuple, ',');
	while (rgb_elemnts[++elemnt])
		ptr[elemnt] = ft_atof(rgb_elemnts[elemnt]);
	ptr[elemnt] = w;
	free_split(rgb_elemnts);
}