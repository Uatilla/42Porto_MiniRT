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

int	main(void)
{
	t_minirt	data;

	ft_memset(&data, 0, sizeof(data));
	start_mlx(&data.canvas);

	t_material m;
	m.color = (t_color){1, 0.9, 0.9, 999999};
	m.ambient = 0.1;
	m.diffuse = 0.7;
	m.specular = 0;
	m.shininess = 200;

	t_matrix *sc;
	sc = mtx_create(&data, 4, 4);
	fill_idnty_mtx(sc);
	mtx_scaling(sc, &(t_point){10, 0.01, 10, 1});

	// parse_shape(&data.world, SP, NULL, &m);
	// data.world.objs->mtx_trans = mtx_multiply(&data, sc, data.world.objs->mtx_trans);
	// data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);

	t_matrix *trans_wall_l;
	trans_wall_l = mtx_create(&data, 4, 4);
	fill_idnty_mtx(trans_wall_l);
	mtx_translation(trans_wall_l, &(t_point){0, 0, 5, 1});

	t_matrix *rot_y_left;
	rot_y_left = mtx_create(&data, 4, 4);
	fill_idnty_mtx(rot_y_left);
	mtx_rotation_y(rot_y_left, -M_PI / 4);

	t_matrix *rot_x_left;
	rot_x_left = mtx_create(&data, 4, 4);
	fill_idnty_mtx(rot_x_left);
	mtx_rotation_x(rot_x_left, M_PI / 2);

	t_matrix *sc_lwall;
	sc_lwall = mtx_create(&data, 4, 4);
	fill_idnty_mtx(sc_lwall);
	mtx_scaling(sc_lwall, &(t_point){10, 0.01, 10, 1});

	parse_shape(&data.world, SP, NULL, &m);
	data.world.objs->mtx_trans = mtx_multiply(&data, trans_wall_l, data.world.objs->mtx_trans);
	data.world.objs->mtx_trans = mtx_multiply(&data, rot_y_left, data.world.objs->mtx_trans);
	data.world.objs->mtx_trans = mtx_multiply(&data, rot_x_left, data.world.objs->mtx_trans);
	data.world.objs->mtx_trans = mtx_multiply(&data, sc_lwall, data.world.objs->mtx_trans);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);

	point_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 999999}, &data.world);

	data.camera = camera_construct(WIDTH, HEIGTH, PI / 3);
	data.camera.trans = view_transformation(&(t_point){0, 1.5, -5, 1}, &(t_point){0, 1, 0, 1}, &(t_vector){0, 1, 0, 0});
	data.camera.inver = mtx_inverse(&data, data.camera.trans);
	render(&data);
}

























//
// int	main(void)
// {
// 	t_minirt	data;
//
// 	ft_memset(&data, 0, sizeof(data));
// 	start_mlx(&data.canvas);
//
// 	t_material m;
// 	m.shininess = 100;
// 	m.specular = 0.9;
// 	m.diffuse = 0.9;
// 	m.color = (t_color){1, 0.5, 0.2, 999};
// 	m.ambient = 0.3;
// 	m.min = -1;
// 	m.max = 1;
// 	m.closed = true;
//
// 	// t_matrix *sca;
// 	// sca = mtx_create(&data, 4, 4);
// 	// fill_idnty_mtx(sca);
// 	// mtx_scaling(sca, &(t_point){0.2, 0.2, 0.2, 1});
// 	//
// 	// t_matrix *trans;
// 	// trans = mtx_create(&data, 4, 4);
// 	// fill_idnty_mtx(trans);
// 	// mtx_translation(trans, &(t_point){2, 0, 0, 1});
// 	//
// 	t_matrix *rot;
// 	rot = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(rot);
// 	mtx_rotation_z(rot, PI / 5);
//
// 	t_matrix *rot_2;
// 	rot_2 = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(rot_2);
// 	mtx_rotation_x(rot_2, PI / 2);
//
// 	t_matrix *rot_3;
// 	rot_3 = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(rot_3);
// 	mtx_rotation_y(rot_3, PI / 3);
//
// 	parse_shape(&data.world, SP, NULL, &m);
// 	// data.world.objs->mtx_trans = mtx_multiply(&data, sca, data.world.objs->mtx_trans);
// 	// data.world.objs->mtx_trans = mtx_multiply(&data, trans, data.world.objs->mtx_trans);
// 	data.world.objs->mtx_trans = mtx_multiply(&data, rot_2, data.world.objs->mtx_trans);
// 	data.world.objs->mtx_trans = mtx_multiply(&data, rot_3, data.world.objs->mtx_trans);
// 	data.world.objs->mtx_trans = mtx_multiply(&data, rot, data.world.objs->mtx_trans);
// 	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);
//
// 	// t_vector normal;
// 	// 
// 	// normal = normal_at(data.world.objs, &(t_point){0, 2, 0.5, 1}, &data);
// 	//
// 	// printf("%f %f %f\n", normal.x, normal.y, normal.z);
//
// 	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1}, &data.world);
// 	data.camera = camera_construct(WIDTH, HEIGTH, PI / 3);
// 	data.camera.trans = view_transformation(&(t_point){0, 0, -5, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
// 	data.camera.inver = mtx_inverse(&data, data.camera.trans);
// 	render(&data);
// }






































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

// int	main(int argc, char **argv)
// {
// 	t_minirt	data;
// 	t_material	m1;
// 	t_material	m2;
//
// 	(void)argc;
// 	(void)argv;
// 	(void)m1;
// 	ft_memset(&data, 0, sizeof(data));
// 	chk_input(&data, argc, argv[1]);
// 	set_scene(&data, argv[1]);
// 	start_mlx(&data.canvas);
//
// 	//0) Define the Material of the Center Sphere
// 	
// 	//parse_shape(&data.world, SP);
//
// 	//1) Scaling
// 	/*t_matrix *sc_center;
// 	sc_center = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(sc_center);
// 	mtx_scaling(sc_center, &(t_point){1, 1, 1, 1});
// 	data.world.objs->mtx_trans = mtx_multiply(&data, sc_center, data.world.objs->mtx_trans);*/
// 	
// 	//2) Applying all modifications made.
// 	//data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);
// 	
//
// 	//0) Define the Material of the Left Sphere
// 	/*m2 = parse_material(OPC);
// 	parse_shape(&data.world, &m2, SP);
//
//
// 	//1) Scaling
// 	t_matrix *sc_left;
// 	sc_left = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(sc_left);
// 	mtx_scaling(sc_left, &(t_point){1, 1, 1, 1});
// 	data.world.objs->mtx_trans = mtx_multiply(&data, sc_left, data.world.objs->mtx_trans);
//
// 	//2) Moving
// 	t_matrix *trans_left;
// 	trans_left = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(trans_left);
// 	mtx_translation(trans_left, &(t_point){5, 0, 0, 1});
// 	data.world.objs->mtx_trans = mtx_multiply(&data, trans_left, data.world.objs->mtx_trans);
//
// 	//3) Rotating.
// 	t_matrix *rotx_left;
// 	rotx_left = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(rotx_left);
// 	mtx_rotation_x(rotx_left, 70);
// 	data.world.objs->mtx_trans = mtx_multiply(&data, rotx_left, data.world.objs->mtx_trans);*/
//
//
// 	//4) Applying all modifications made.
// 	//data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);
//
// 	//Setting light of the scene;
// 	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1}, &data.world);
// 	
//
// 	//Building Camera
// 	data.camera = camera_construct(WIDTH, HEIGTH, PI / 3);
// 	//data.camera.trans = view_transformation(&(t_point){-50, 0, 20, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
// 	data.camera.trans = view_transformation(&(t_point){0, 0, -15, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
// 	
// 	
// 	//ERRO A CAMERA PRECISA RODAR DENTRO DO PROPRIO EIXO 
// 	//Trying to rotate the camera on its own axis.
// 	/*t_matrix *cam_transl;
// 	cam_transl = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(cam_transl);
// 	mtx_translation(cam_transl, &(t_point){-25, 10, 0, 1});
// 	data.camera.trans = mtx_multiply(&data, cam_transl, data.camera.trans);*/
//
// 	data.camera.inver = mtx_inverse(&data, data.camera.trans);
//
// 	//Rendering Image on the screen.
// 	render(&data);
//
// 	/*ATTENTION THIS CODE WAS MOVED TO RENDER:
// 	
// 	clean_world(&data.world);
// 	clean_matrix(&data, data.camera.trans, 0);
// 	clean_matrix(&data, data.camera.inver, 0);*/
// }
