/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/23 19:24:05 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


//MAP LIGHT MUST BE 
/*void	parse_light(t_minirt *mrt, char **line)
{
	get_tuple(&mrt->world.light->position, line[1], 1);
	mrt->world.light->bright_ratio = ft_atof(line[2]);
	get_tuple(&mrt->world.light->intensity, line[2], 999999);
}*/

void	parse_camera(t_minirt *mrt, char **line)
{
	get_tuple(&mrt->camera.cam_pos, line[1], 1);
	get_tuple(&mrt->camera.cam_norm_vect, line[2], 0);
	mrt->camera.fov = ft_atof(line[3]);
}

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
			get_tuple(&mrt->world.ambient->color, line[n_elem], 999999);
	}
}

int	main(int argc, char **argv)
{
	t_minirt	data;

	ft_memset(&data, 0, sizeof(data));
	chk_input(&data, argc, argv[1]);
	set_scene(&data, argv[1]);
	start_mlx(&data.canvas);

	printf("BR Ratio: %f\n", data.world.light->bright_ratio);
	//Define the Material of the Center Sphere
	t_material m_1;
	m_1.color = (t_color){1, 0.7, 0.3, 999999};
	m_1.ambient = 0.1;
	m_1.diffuse = 0.7;
	m_1.shininess = 200;
	m_1.specular = 0.8;

	//Parsing First Center Sphere
	parse_shape(&data.world, &m_1, SP);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);

	//Define the Material of the Left Sphere
	t_material m_2;
	m_2.color = (t_color){0.7, 1, 0.3, 999999};
	m_2.ambient = 0.1;
	m_2.diffuse = 0.7;
	m_2.shininess = 200;
	m_2.specular = 0.8;

	//Manipulating the Left Sphere
	t_matrix *sc_left;
	sc_left = mtx_create(&data, 4, 4);
	fill_idnty_mtx(sc_left);
	mtx_scaling(sc_left, &(t_point){0.5, 0.5, 0.5, 1});

	t_matrix *trans_left;
	trans_left = mtx_create(&data, 4, 4);
	fill_idnty_mtx(trans_left);
	mtx_translation(trans_left, &(t_point){-2, 0, 0, 1});

	//Parsing Second Left Sphere
	parse_shape(&data.world, &m_2, SP);
	data.world.objs->mtx_trans = mtx_multiply(&data, sc_left, data.world.objs->mtx_trans);
	data.world.objs->mtx_trans = mtx_multiply(&data, trans_left, data.world.objs->mtx_trans);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);


	//Setting light of the scene;
	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1}, &data.world);


	//Building Camera
	data.camera = camera_construct(WIDTH, HEIGTH, PI / 3);
	data.camera.trans = view_transformation(&(t_point){0, 0, -5, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
	data.camera.inver = mtx_inverse(&data, data.camera.trans);

	//Rendering Image on the screen.
	render(&data);
	/*ATTENTION THIS CODE WAS MOVED TO RENDER:
	
	clean_world(&data.world);
	clean_matrix(&data, data.camera.trans, 0);
	clean_matrix(&data, data.camera.inver, 0);*/
}