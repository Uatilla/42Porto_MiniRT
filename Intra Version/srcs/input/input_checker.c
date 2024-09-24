/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:29:19 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/24 15:58:06 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Check the syntax of each element type.
/// @param line Elements inside in the Scene.
/// @param chk_stx Temp structure to track syntax errors.
void	chk_type_objs(t_minirt *mrt, char **line, t_checkstx *chk_stx)
{
	(void)chk_stx;
	if (line[0])
	{
		if (!ft_strcmp(line[0], "A"))
			input_chk_ambient(mrt, line, chk_stx);
		else if (!ft_strcmp(line[0], "C"))
			input_chk_camera(mrt, line, chk_stx);
		else if (!ft_strcmp(line[0], "L"))
			input_chk_light(mrt, line, chk_stx);
		else if (!ft_strcmp(line[0], "sp"))
			input_chk_sphere(mrt, line, chk_stx);
		else if (!ft_strcmp(line[0], "pl"))
			input_chk_plane(mrt, line, chk_stx);
		else if (!ft_strcmp(line[0], "cy") || !ft_strcmp(line[0], "cn"))
			input_chk_cyl_con(mrt, line, chk_stx);
	}
	free_split(line);
}

/// @brief Start verifying the Scene syntax.
/// @param data Main program structure.
/// @param file Scene file.
t_checkstx	chk_scene_objs(t_minirt *data, int file)
{
	char		*line;
	char		*line_trimmed;
	char		**line_cleaned;
	t_checkstx	chk_stx;

	ft_memset(&chk_stx, 0, sizeof(t_checkstx));
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
		check_dup(line_cleaned[0], &chk_stx);
		check_initials(line_cleaned[0], &chk_stx);
		chk_type_objs(data, line_cleaned, &chk_stx);
		if (chk_stx.count_err_stx > 0)
			break ;
	}
	return (chk_stx);
}

bool	check_extension(char *str, char *ext)
{
	int		i;
	char	*substr;

	(void)ext;
	if (ft_strlen(str) < ft_strlen(ext))
		return (False);
	substr = ft_substr(str, ft_strlen(str) - ft_strlen(ext), ft_strlen(ext));
	if (!ft_strcmp(substr, ext))
	{
		free(substr);
		return (True);
	}
	else
	{
		free(substr);
		return (False);
	}
}

void	display_errors(t_minirt *mrt, t_checkstx *chk_stx)
{
	if (chk_stx->count_a > 1 || chk_stx->count_c > 1)
		ft_error(mrt, "ERROR: Duplicated elements (A or C) found.\n", 1);
	if (chk_stx->count_err_stx > 0)
		ft_error(mrt, "ERROR: Invalid scene syntax.\n", 1);
	if (chk_stx->count_preset_err > 0)
		ft_error(mrt, "ERROR: Invalid preset.\n\
		[OPTIONAL] Use one valid or keep it blank:\n\
		MATTE 'MAT', SATIN 'SAT',\n\
		METALLIC 'MTL' or MIRROR 'MIR'.\n", 1);
	if (chk_stx->count_pattern_err > 0)
		ft_error(mrt, "ERROR: Check pattern.\n\
		[OPTIONAL] Use one valid or keep it as 'DEFAULT'\n\
		'PC', 'GR', 'RNG' or 'CHK'.\n", 1);
	if (chk_stx->count_err_bump > 0)
		ft_error(mrt, "ERROR: Check if Bumpmaps is 'BUMP'.\n", 1);
	if (chk_stx->count_err_init > 0)
		ft_error(mrt, "ERROR: A, C or L must be UPPERCASE\n", 1);
	if (chk_stx->count_err_orien_cam > 0)
		ft_error(mrt, "ERROR: Camera must have an orientation\n\
			(0, 0, 0) is not allowed.\n", 1);
}

/// @brief Verify scene file if its available or has syntax errors.
/// @param mrt Main structure.
/// @param argc Number os args.
/// @param file Scene file as string.
void	chk_input(t_minirt *mrt, int argc, char *file)
{
	int			fd;
	t_checkstx	chk_stx;

	if (argc != 2)
	{
		ft_error(NULL, "ERROR: Input invalid!\n\
		Try: ./minirt <scene>.rt\n", 0);
		clear_exit(NULL, 1);
	}
	if (!check_extension(file, ".rt"))
	{
		ft_error(NULL, "ERROR: Input invalid!\n\
		The input doesn't have extension '.rt'.\n", 0);
		clear_exit(NULL, 1);
	}
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
	{
		ft_error(NULL, "ERROR: Failed to open the file.\
		Try another one.\n", 0);
		clear_exit(NULL, 1);
	}
	chk_stx = chk_scene_objs(mrt, fd);
	close (fd);
	display_errors(mrt, &chk_stx);
	printf("INPUT\t\t[OK]\n");
}
