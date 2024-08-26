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

/*

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
*/

int	main(void)
{
	t_minirt	data;

	ft_memset(&data, 0, sizeof(data));
	start_mlx(&data.canvas);

	t_material m_1;
	m_1.color = (t_color){1, 0.7, 0.3, 999999};
	m_1.ambient = 0.1;
	m_1.diffuse = 0.7;
	m_1.shininess = 200;
	m_1.specular = 0.8;

	parse_shape(&data.world, &m_1, SP);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);

	t_material m_2;
	m_2.color = (t_color){0.7, 1, 0.3, 999999};
	m_2.ambient = 0.1;
	m_2.diffuse = 0.7;
	m_2.shininess = 200;
	m_2.specular = 0.8;

	t_matrix *sc_left;
	sc_left = mtx_create(&data, 4, 4);
	fill_idnty_mtx(sc_left);
	mtx_scaling(sc_left, &(t_point){0.5, 0.5, 0.5, 1});

	t_matrix *trans_left;
	trans_left = mtx_create(&data, 4, 4);
	fill_idnty_mtx(trans_left);
	mtx_translation(trans_left, &(t_point){-2, 0, 0, 1});

	parse_shape(&data.world, &m_2, SP);
	data.world.objs->mtx_trans = mtx_multiply(&data, sc_left, data.world.objs->mtx_trans);
	data.world.objs->mtx_trans = mtx_multiply(&data, trans_left, data.world.objs->mtx_trans);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);

	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1}, &data.world);
	data.camera = camera_construct(WIDTH, HEIGTH, PI / 3);
	data.camera.trans = view_transformation(&(t_point){0, 0, -5, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
	data.camera.inver = mtx_inverse(&data, data.camera.trans);
	render(&data);
	/*ATTENTION THIS CODE WAS MOVED TO RENDER:
	
	clean_world(&data.world);
	clean_matrix(&data, data.camera.trans, 0);
	clean_matrix(&data, data.camera.inver, 0);*/
}