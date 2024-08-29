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

t_material	parse_material(enum e_mat material)
{
	t_material m;

	ft_memset(&m, 0, sizeof(t_material));
	if (material == OPC)
	{
		m.color = (t_color){0.0392156, 0, 1, 999999};
		m.ambient = 0.1;
		m.diffuse = 0.7;
		m.shininess = 200;
		m.specular = 0.8;
	}
	return (m);
}

int	main(int argc, char **argv)
{
	t_minirt	data;
	t_material	m1;
	t_material	m2;

	(void)argc;
	(void)argv;
	(void)m1;
	ft_memset(&data, 0, sizeof(data));
	chk_input(&data, argc, argv[1]);
	set_scene(&data, argv[1]);
	start_mlx(&data.canvas);

	//0) Define the Material of the Center Sphere
	m1 = parse_material(OPC);
	parse_shape(&data.world, &m1, SP);

	//1) Scaling
	t_matrix *sc_center;
	sc_center = mtx_create(&data, 4, 4);
	fill_idnty_mtx(sc_center);
	mtx_scaling(sc_center, &(t_point){2, 2, 2, 1});
	data.world.objs->mtx_trans = mtx_multiply(&data, sc_center, data.world.objs->mtx_trans);
	
	//2) Applying all modifications made.
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);
	

	//0) Define the Material of the Left Sphere
	/*m2 = parse_material(OPC);
	parse_shape(&data.world, &m2, SP);


	//1) Scaling
	t_matrix *sc_left;
	sc_left = mtx_create(&data, 4, 4);
	fill_idnty_mtx(sc_left);
	mtx_scaling(sc_left, &(t_point){1, 1, 1, 1});
	data.world.objs->mtx_trans = mtx_multiply(&data, sc_left, data.world.objs->mtx_trans);

	//2) Moving
	t_matrix *trans_left;
	trans_left = mtx_create(&data, 4, 4);
	fill_idnty_mtx(trans_left);
	mtx_translation(trans_left, &(t_point){5, 0, 0, 1});
	data.world.objs->mtx_trans = mtx_multiply(&data, trans_left, data.world.objs->mtx_trans);


	//3) Rotating.
	t_matrix *rotx_left;
	rotx_left = mtx_create(&data, 4, 4);
	fill_idnty_mtx(rotx_left);
	mtx_rotation_x(rotx_left, 70);
	data.world.objs->mtx_trans = mtx_multiply(&data, rotx_left, data.world.objs->mtx_trans);*/


	//4) Applying all modifications made.
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);


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
	


	/*ATTENTION THIS CODE WAS MOVED TO RENDER:
	
	clean_world(&data.world);
	clean_matrix(&data, data.camera.trans, 0);
	clean_matrix(&data, data.camera.inver, 0);*/
}