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

/// @brief Direct which function should verify the line.
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
			parse_sphere(mrt, line);
		else if (!ft_strcmp(line[0], "pl"))
			parse_plane(mrt, line);
		else if (!ft_strcmp(line[0], "cy"))
			parse_cylinder(mrt, line);
	}
	free_split(line);
}

/// @brief Check input scene file line by line.
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
	//Parse material
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
