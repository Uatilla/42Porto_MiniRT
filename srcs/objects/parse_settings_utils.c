/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:19:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/28 20:19:45 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Select the preset for each object.
/// @param line Input line to be checked.
/// @param  type Object type.
/// @return Material settings.
t_material	parse_material(char **line, enum e_id type)
{
	t_material	m;
	char		*preset;

	ft_memset(&m, 0, sizeof(t_material));
	if ((type == SP || type == PL) && line[4])
		preset = line[4];
	else if (type == CY && line[5])
		preset = line[5];
	if (!ft_strcmp("MAT", preset) || !preset)
	{
		m.ambient = 0.3;
		m.diffuse = 0.7;
		m.shininess = 10;
		m.specular = 0.1;
	}
	else if (!ft_strcmp("MTL", preset))
	{
		m.ambient = 0.1;
		m.diffuse = 0.3;
		m.shininess = 200;
		m.specular = 0.9;
	}
	else if (!ft_strcmp("SAT", preset))
	{
		m.ambient = 0.25;
		m.diffuse = 0.5;
		m.shininess = 50;
		m.specular = 0.5;
	}
	return (m);
}

/// @brief Build each obj of the scene.
/// @param mrt Main structure.
/// @param line Line to be verified.
void	parse_line(t_minirt *mrt, char **line)
{
	if (line[0])
	{
		if (!ft_strcmp(line[0], "A"))
			parse_ambient(mrt, line);
		else if (!ft_strcmp(line[0], "C"))
			parse_camera(mrt, line);
		else if (!ft_strcmp(line[0], "L"))
			parse_light(mrt, line);
		else if (!ft_strcmp(line[0], "sp"))
			parse_shape(mrt, SP, line);
		else if (!ft_strcmp(line[0], "pl"))
			parse_shape(mrt, PL, line);
		else if (!ft_strcmp(line[0], "cy"))
			parse_shape(mrt, CY, line);
	}
	free_split(line);
}

/// @brief Check input scene file line by line ans sets each objs.
/// @param mrt Main structure.
/// @param file Scene file content.
void	set_scene(t_minirt *mrt, char *file)
{
	char		*line;
	char		*line_trimmed;
	char		**line_cleaned;
	int			fd;

	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		clear_exit(NULL, 1);
	mrt->world.obj_selected = 0;
	mrt->world.n_objs = 0;
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
void	fill_tuple(t_tuple *tuple, char *str_tuple, int w)
{
	int			elemnt;
	float		*ptr;
	char		**rgb_elemnts;

	ptr = (float *)tuple;
	elemnt = -1;
	rgb_elemnts = ft_split(str_tuple, ',');
	while (rgb_elemnts[++elemnt])
		ptr[elemnt] = ft_atof(rgb_elemnts[elemnt]);
	ptr[elemnt] = w;
	free_split(rgb_elemnts);
}

/// @brief Takes a string and returns its corrresponding tuple.
/// @param str_tuple Source of the tuple elements.
/// @param w Content of the W pos in the tuple.
/// @return Tuple with the string content.
t_tuple	get_tuple(char *str_tuple, int w)
{
	int			elemnt;
	float		*ptr;
	t_tuple		tup_res;
	char		**rgb_elemnts;

	elemnt = -1;
	ptr = (float *)&tup_res;
	rgb_elemnts = ft_split(str_tuple, ',');
	while (rgb_elemnts[++elemnt])
		ptr[elemnt] = ft_atof(rgb_elemnts[elemnt]);
	ptr[elemnt] = w;
	free_split(rgb_elemnts);
	return (tup_res);
}
