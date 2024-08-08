/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:29:19 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/01 20:29:21 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	chk_input(int argc, char *file)
{
	int	fd;

	if (argc != 2)
	{
		ft_error("ERROR: Input invalid!\n  Try:\n\t./minirt <scene>.rt\n");
		clear_exit(NULL, 1);
	}
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
	{
		ft_error("ERROR: Failed to open the scene, try another one.\n");
		clear_exit(NULL, 1);
	}
	return (fd);
}
