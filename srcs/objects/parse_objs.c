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

void	free_split(char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		free(line[i]);
	free(line);
}

void	check_range(char *val, t_checkstx *chk_stx, float l_range, float u_range)
{
	float value;

	value = ft_atof(val);
	if (value < l_range || value > u_range)
		chk_stx->count_err_stx++;
}

/// @brief Check the syntax of Ambient Element.
/// @param line Elements inside Ambient line in the map.
/// @param chk_stx Temp
void	parse_ambient(char **line, t_checkstx *chk_stx)
{
	int	i;
	int	color;
	char	**rgb_elemts;

	i = -1;
	while (line[++i])
	{
		if (i == 1)
			check_range(line[i], chk_stx, 0.0, 1.0);
		else if (i == 2)
		{
			//check_color(line, i, chk_stx);
			rgb_elemts = ft_split(line[i], ',');
			color = -1;
			while (rgb_elemts[++color])
				check_range(rgb_elemts[color], chk_stx, 0.0,255.0);
			if (color > 3)
				chk_stx->count_err_stx++;
			free_split(rgb_elemts);
		}
	}
	if (i != 3)
		chk_stx->count_err_stx++;

}

void	parse_type(char **line, t_checkstx *chk_stx)
{
	(void)chk_stx;
	if (line[0])
	{
		
		if (!ft_strcmp(line[0], "A"))
			parse_ambient(line, chk_stx);
		else if (!ft_strcmp(line[0], "C"))
			printf("C\n");
		else if (!ft_strcmp(line[0], "L"))
			printf("L\n");
		else if (!ft_strcmp(line[0], "sp"))
			printf("sp\n");
		else if (!ft_strcmp(line[0], "pl"))
			printf("pl\n");
		else if (!ft_strcmp(line[0], "cy"))
			printf("cy\n");
	}
	free_split(line);
}

void	check_dup(char *obj_type, t_checkstx *chk_stx)
{
	if (obj_type)
	{
		if (!ft_strcmp(obj_type, "A"))
			chk_stx->count_a++;
		else if (!ft_strcmp(obj_type, "C"))
			chk_stx->count_c++;
		else if (!ft_strcmp(obj_type, "L"))
			chk_stx->count_l++;
	}
}

void	parse_objects(enum e_id type, t_minirt *data, int file, t_material *m)
{
	bool	stx_failed;
	char	*line;
	char	*line_trimmed;
	char	**line_cleaned;
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
		line_cleaned = ft_split(line_trimmed,' ');
		free(line_trimmed);
		check_dup(line_cleaned[0], &chk_sintax);
		parse_type(line_cleaned, &chk_sintax);
	}
	if (chk_sintax.count_a > 1 || chk_sintax.count_l > 1 || chk_sintax.count_c > 1)
		ft_error(data, "ERROR: Duplicated elements found.\n", 1);
	if (chk_sintax.count_err_stx > 0)
		ft_error(data, "ERROR: Invalid Map Syntax\n", 1);
	if (type == SP)
		parse_sphere(&data->world, m);
}

/*
*	adds a object node to the top of the objcts stack
*	creats a stack if is empty
*/
void	parse_sphere(t_world *world, t_material *m)
{
	t_sphere	*sphere;

	if (world->objs == NULL)
	{
		world->objs = ft_calloc(sizeof(t_sphere), 1);
		if (world->objs == NULL)
			clear_exit(NULL, errno);
		fill_sphere(world->objs, m);
		return ;
	}
	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (sphere == NULL)
		clear_exit(NULL, errno);
	fill_sphere(sphere, m);
	sphere->next = world->objs;
	world->objs = sphere;
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
