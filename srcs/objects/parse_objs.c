/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:04:30 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/07 21:06:28 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Check the syntax of each element type.
/// @param line Elements inside in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	parse_type(t_minirt *mrt, char **line, t_checkstx *chk_stx)
{
	(void)chk_stx;
	if (line[0])
	{
		if (!ft_strcmp(line[0], "A"))
			parse_ambient(mrt, line, chk_stx);
		else if (!ft_strcmp(line[0], "C"))
			parse_camera(mrt, line, chk_stx);
		else if (!ft_strcmp(line[0], "L"))
			parse_light(mrt, line, chk_stx);
		else if (!ft_strcmp(line[0], "sp"))
			parse_sphere(mrt, line, chk_stx);
		else if (!ft_strcmp(line[0], "pl"))
			parse_plane(mrt, line, chk_stx);
		else if (!ft_strcmp(line[0], "cy"))
			parse_cylinder(mrt, line, chk_stx);
	}
	free_split(line);
}

/// @brief Start verifying the Scene syntax.
/// @param  
/// @param data Main program structure.
/// @param file Scene file.
void	parse_objects(enum e_identifyer type, t_minirt *data, int file)
{
	char		*line;
	char		*line_trimmed;
	char		**line_cleaned;
	t_checkstx	chk_sintax;

	ft_memset(&chk_sintax, 0, sizeof(t_checkstx));
	while (1)
	{
		line = get_next_line(file);
		if (!line)
			break ;
		ft_replace(line, '\t', ' ');
		line_trimmed = ft_strtrim(line, "\n");
		free(line);
		line_cleaned = ft_split(line_trimmed, ' ');
		free(line_trimmed);
		check_dup(line_cleaned[0], &chk_sintax);
		parse_type(data, line_cleaned, &chk_sintax);
	}
	if (chk_sintax.count_a > 1 || chk_sintax.count_l > 1
		|| chk_sintax.count_c > 1)
		ft_error(data, "ERROR: Duplicated elements found.\n", 1);
	if (chk_sintax.count_err_stx > 0)
		ft_error(data, "ERROR: Invalid Scene Syntax\n", 1);
	if (type == SP)
		parse_sphere2(data);
}


/*
*	adds a object node to the top of the objcts stack
*	creats a stack if is empty
*/
void	parse_sphere2(t_minirt *data)
{
	t_sphere	*sphere;

	if (data->objs == NULL)
	{
		data->objs = ft_calloc(sizeof(t_sphere), 1);
		if (data->objs == NULL)
			clear_exit(data, errno);
		fill_sphere(((t_sphere *)data->objs), data);
		return ;
	}
	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (sphere == NULL)
		clear_exit(data, errno);
	fill_sphere(sphere, data);
	sphere->next = data->objs;
	data->objs = sphere;
}

void	fill_sphere(t_sphere *sp, t_minirt *data)
{
	t_matrix	*mtx;

	mtx = mtx_create(data, 4, 4);
	fill_idnty_mtx(mtx);
	sp->type = SP;
	sp->mtx_trans = mtx;
	//mtx_translation(mtx, &(t_tuple){1, 1, 0, 1});
	set_materials(&sp->material);
}

/*
*	fisrst inplementation
*/
void	set_materials(t_material *material)
{
	material->color = (t_color){1, 0.2, 0.8, 999999};
	material->ambient = 0.1;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 100.0;
}
