/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/22 16:58:48 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*void	parse_camera(t_minirt *mrt, char **line)
{
	int	n_elem;

	n_elem = -1;
	*(mrt->camera) = (t_camera *)ft_calloc(sizeof(t_camera), 1);
	if (!mrt->camera)
		clear_exit(mrt, 1);
	while (line[++n_elem])
	{
		if (n_elem == 1)
			get_tuple(&mrt->camera.cam_pos, line[n_elem]);
		else if (n_elem == 2)
			get_tuple(&mrt->camera.cam_norm_vect, line[n_elem]);
		else if (n_elem == 3)
			mrt->camera.fov = ft_atof(line[n_elem]);
	}
}*/

void	parse_ambient(t_minirt *mrt, char **line)
{
	int	n_elem;

	n_elem = -1;
	mrt->world.ambient = (t_ambient *)ft_calloc(sizeof(t_ambient), 1);
	if (!mrt->world.ambient)
		clear_exit(mrt, 1);
	while (line[++n_elem])
	{
		if (n_elem == 1)
			mrt->world.ambient->ratio = ft_atof(line[n_elem]);
		else if (n_elem == 2)
			get_tuple(&mrt->world.ambient->color, line[n_elem]);
	}
}

int	main(int argc, char **argv)
{
	t_minirt	data;

	ft_memset(&data, 0, sizeof(data));
	chk_input(&data, argc, argv[1]);
	set_scene(&data, argv[1]);
	

	//Function to be better called.
	free(data.world.ambient);


	start_mlx(&data.canvas);
	data.ray.origin = (t_point){0, 0, -5, 1};
	mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
	mlx_key_hook(data.canvas.win, &handle_key_event, &data);
	mlx_loop(data.canvas.mlx);
	clear_exit(&data, 0);
}