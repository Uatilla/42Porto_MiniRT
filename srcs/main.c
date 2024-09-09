/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/29 17:16:19 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_minirt	data;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(data));
	chk_input(&data, argc, argv[1]);
	set_scene(&data, argv[1]);
	start_mlx(&data.canvas);

	//Setting light of the scene;
	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1}, &data.world);
	

	//Building Camera
	data.camera = camera_construct(WIDTH, HEIGTH, PI / 3);
	//data.camera.trans = view_transformation(&(t_point){-50, 0, 20, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
	data.camera.trans = view_transformation(&(t_point){0, 0, -15, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
	
	data.camera.inver = mtx_inverse(&data, data.camera.trans);
	render(&data);
}
