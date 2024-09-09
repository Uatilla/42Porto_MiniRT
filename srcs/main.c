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

t_material	parse_material(char **line, enum e_id type)
{
	t_material m;
	char *preset;

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
	
	
	//ERRO A CAMERA PRECISA RODAR DENTRO DO PROPRIO EIXO 
	//Trying to rotate the camera on its own axis.
	/*t_matrix *cam_transl;
	cam_transl = mtx_create(&data, 4, 4);
	fill_idnty_mtx(cam_transl);
	mtx_translation(cam_transl, &(t_point){-25, 10, 0, 1});
	data.camera.trans = mtx_multiply(&data, cam_transl, data.camera.trans);*/

	data.camera.inver = mtx_inverse(&data, data.camera.trans);

	//Rendering Image on the screen.
	render(&data);
}
