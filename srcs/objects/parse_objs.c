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

void	free_split(char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		free(line[i]);
	free(line);
}

/// @brief Verify if the element is under the valid value range.
/// @param val Value to be checked.
/// @param chk_stx Temp structure to track syntax errors.
/// @param l_range Lower valid range.
/// @param u_range Upper valid range.
void	check_range(char *val, t_checkstx *chk_stx, float *range_limts)
{
	float value;

	value = ft_atof(val);
	if (value < range_limts[0] || value > range_limts[1])
		chk_stx->count_err_stx++;
}

/// @brief Verify if the string has only three elmnts and is in a valid range.
/// @param line Elements in the line to be checked.
/// @param elemnt_str Element index in line. 
/// @param chk_stx Temp structure to track syntax errors.
/// @param range_limts Float Array limits.
void	check_elemnt(char **line, int elemnt_str, t_checkstx *chk_stx, float *range_limts)
{
	int	color;
	char	**rgb_elemts;

	rgb_elemts = ft_split(line[elemnt_str], ',');
	color = -1;
	while (rgb_elemts[++color])
		if (range_limts)
			check_range(rgb_elemts[color], chk_stx, range_limts);
	if (color > 3)
		chk_stx->count_err_stx++;
	free_split(rgb_elemts);
}

/// @brief Check the syntax of Ambient Element.
/// @param line Elements inside Ambient line in the map.
/// @param chk_stx Temp structure to track syntax errors.
void	parse_ambient(char **line, t_checkstx *chk_stx)
{
	int	n_elem;

	n_elem = -1;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_range(line[n_elem], chk_stx, (float []){0.0, 1.0});
		else if (n_elem == 2)
			check_elemnt(line, n_elem, chk_stx, (float []){0.0, 255.0});
	}
	if (n_elem != 3)
		chk_stx->count_err_stx++;
}

void	parse_camera(char **line, t_checkstx *chk_stx)
{
	int	n_elem;

	n_elem = -1;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_elemnt(line, n_elem, chk_stx, NULL);
		else if (n_elem == 2)
			check_elemnt(line, n_elem, chk_stx, (float []){-1.0, 1.0});
		else if (n_elem == 3)
			check_range(line[n_elem], chk_stx, (float []){0.0, 180.0});
	}
	if (n_elem != 4)
		chk_stx->count_err_stx++;
}

void	parse_light(char **line, t_checkstx *chk_stx)
{
	int	n_elem;

	n_elem = -1;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_elemnt(line, n_elem, chk_stx, NULL);
		else if (n_elem == 2)
			check_range(line[n_elem], chk_stx, (float []){0.0, 1.0});
		else if (n_elem == 3)
			check_elemnt(line, n_elem, chk_stx, (float []){0, 255.0});
	}
	if (n_elem != 4)
		chk_stx->count_err_stx++;
}

void	parse_plane(char **line, t_checkstx *chk_stx)
{
	int	n_elem;

	n_elem = -1;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_elemnt(line, n_elem, chk_stx, NULL);
		else if (n_elem == 2)
			check_elemnt(line, n_elem, chk_stx, (float []){-1.0, 1.0});
		else if (n_elem == 3)
			check_elemnt(line, n_elem, chk_stx, (float []){0, 255.0});
	}
	if (n_elem != 4)
		chk_stx->count_err_stx++;
}

void	check_negative(char *dimension, t_checkstx *chk_stx)
{
	if (atof(dimension) < 0.0)
		chk_stx->count_err_stx++;
}

void	parse_cylinder(char **line, t_checkstx *chk_stx)
{
	int	n_elem;

	n_elem = -1;
	while (line[++n_elem])
	{
		if (n_elem == 1)
			check_elemnt(line, n_elem, chk_stx, NULL);
		else if (n_elem == 2)
			check_elemnt(line, n_elem, chk_stx, (float []){-1.0, 1.0});
		else if (n_elem == 3)
			check_negative(line[n_elem], chk_stx);
		else if (n_elem == 4)
			check_negative(line[n_elem], chk_stx);
		else if (n_elem == 5)
			check_elemnt(line, n_elem, chk_stx, (float []){0, 255.0});
	}
	if (n_elem != 6)
		chk_stx->count_err_stx++;
}

void	parse_type(char **line, t_checkstx *chk_stx)
{
	(void)chk_stx;
	if (line[0])
	{
		//Should we deal with lower A, C, L?
		if (!ft_strcmp(line[0], "A"))
			parse_ambient(line, chk_stx);
		else if (!ft_strcmp(line[0], "C"))
			parse_camera(line, chk_stx);
		else if (!ft_strcmp(line[0], "L"))
			parse_light(line, chk_stx);
		else if (!ft_strcmp(line[0], "sp"))
			printf("sp\n");
		else if (!ft_strcmp(line[0], "pl"))
			parse_plane(line, chk_stx);
		else if (!ft_strcmp(line[0], "cy"))
			parse_cylinder(line, chk_stx);
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

void	parse_objects(enum e_identifyer type, t_minirt *data, int file)
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
		parse_sphere(data);
}

/*
*	adds a object node to the top of the objcts stack
*	creats a stack if is empty
*/
void	parse_sphere(t_minirt *data)
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
