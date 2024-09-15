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

	ft_memset(&data, 0, sizeof(data));
	chk_input(&data, argc, argv[1]);
	set_scene(&data, argv[1]);
	start_mlx(&data.canvas);
	render(&data);

	//WALL

	//WALL1
	/*t_material m;
	m.pattern.has = false;
	m.color = (t_color){1, 0.9, 0.9, 999999};
	m.ambient = 0.1;
	m.diffuse = 0.7;
	m.specular = 0;
	m.shininess = 200;
	m.pattern = stripe_pattern(&(t_color){0, 0, 0, 0}, &(t_color){1, 0, 0, 1}, CHK);
	m.pattern.inver = mtx_inverse(&data, m.pattern.trans);

	parse_shape(&data.world, PL, NULL, &m);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);*/

	

	//WALL2
	/*t_material wall;
	wall.pattern.has = false;
	wall.color = (t_color){1, 0.9, 0.9, 999999};
	wall.ambient = 0.1;
	wall.diffuse = 0.7;
	wall.specular = 0;
	wall.shininess = 200;
	wall.pattern = stripe_pattern(&(t_color){0, 0, 0, 0}, &(t_color){1, 0, 0, 1}, RNG);
	wall.pattern.inver = mtx_inverse(&data, wall.pattern.trans);

	t_matrix	*wall_r_x;
	wall_r_x = mtx_create(&data, 4, 4);
	fill_idnty_mtx(wall_r_x);
	mtx_rotation_x(wall_r_x, M_PI / 2);

	t_matrix	*wall_trans;
	wall_trans = mtx_create(&data, 4, 4);
	fill_idnty_mtx(wall_trans);
	mtx_translation(wall_trans, &(t_point){0, 0, 5, 1});

	parse_shape(&data.world, PL, NULL, &wall);
	data.world.objs->mtx_trans = mtx_multiply(&data, wall_r_x, data.world.objs->mtx_trans);
	data.world.objs->mtx_trans = mtx_multiply(&data, wall_trans, data.world.objs->mtx_trans);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);*/
	

	

	//SPHERES
	//SP1
	/*t_material midle;
	midle.pattern.has = false;
	midle.color = (t_color){0.1, 1, 0.5, 1};
	midle.diffuse = 0.7;
	midle.ambient = 0.1;
	midle.specular = 0.3;
	midle.shininess = 200;
	midle.pattern = stripe_pattern(&(t_color){0, 1, 0, 0}, &(t_color){1, 0.33, 0.9, 1}, STR);
	midle.pattern.inver = mtx_inverse(&data, midle.pattern.trans);



	t_matrix *trans_m;
	trans_m = mtx_create(&data, 4, 4);
	fill_idnty_mtx(trans_m);
	mtx_translation(trans_m, &(t_point){-0.5, 1, 0.5, 1});

	parse_shape(&data.world, SP, NULL, &midle);
	data.world.objs->mtx_trans = mtx_multiply(&data, trans_m, data.world.objs->mtx_trans);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);*/





	//SP2
	/*t_material right;
	right.pattern.has = false;
	right.color = (t_color){0.5, 1, 0.1, 1};
	right.diffuse = 0.7;
	right.ambient = 0.1;
	right.specular = 0.3;
	right.shininess = 200;

	t_matrix *trans_right;
	trans_right = mtx_create(&data, 4, 4);
	fill_idnty_mtx(trans_right);
	mtx_translation(trans_right, &(t_point){1.5, 0.5, -0.5, 1});

	t_matrix *sc_right;
	sc_right = mtx_create(&data, 4, 4);
	fill_idnty_mtx(sc_right);
	mtx_scaling(sc_right, &(t_point){0.5, 0.5, 0.5, 1});



	parse_shape(&data.world, SP, NULL, &right);
	data.world.objs->mtx_trans = mtx_multiply(&data, sc_right, data.world.objs->mtx_trans);
	data.world.objs->mtx_trans = mtx_multiply(&data, trans_right, data.world.objs->mtx_trans);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);*/












	//CYLINDRO
	
	/*t_material cylindro;
	cylindro.pattern.has = false;


	cylindro.color = (t_color){1, 0.8, 0.1, 1};


	cylindro.diffuse = 0.7;
	cylindro.ambient = 0.1;
	cylindro.specular = 0.9;
	cylindro.shininess = 200;


	cylindro.closed = true;
	cylindro.min = -1;
	cylindro.max = 2;


	//Translation Temp
	t_matrix	*cy_trans;
	cy_trans = mtx_create(&data, 4, 4);
	fill_idnty_mtx(cy_trans);
	mtx_translation(cy_trans, &(t_point){-1.5, 0.5, -0.5, 1});
	printf("Main: After Translation:\n");
	mtx_print(cy_trans);
	printf("=======\n");


	//Scale
	t_matrix	*cy_sc;
	cy_sc = mtx_create(&data, 4, 4);
	fill_idnty_mtx(cy_sc);
	mtx_scaling(cy_sc, &(t_point){0.5, 0.5, 0.5, 1});
	printf("Main: After Scaling:\n");
	mtx_print(cy_trans);
	printf("=======\n");
	data.world.objs->mtx_trans = mtx_multiply(&data, cy_sc, data.world.objs->mtx_trans);
	printf("Main: After Multiply Scaling with trans:\n");
	mtx_print(cy_trans);
	printf("=======\n");*/



	/*t_matrix	*cy_rot;
	cy_rot = mtx_create(&data, 4, 4);
	fill_idnty_mtx(cy_rot);
	mtx_rotation_x(cy_rot, -M_PI / 6);



	t_matrix	*cy_rot_y;
	cy_rot_y = mtx_create(&data, 4, 4);
	fill_idnty_mtx(cy_rot_y);
	mtx_rotation_y(cy_rot_y, -M_PI / 6);*/


	//parse_shape(&data.world, CY, NULL, &cylindro);
	//data.world.objs->mtx_trans = mtx_multiply(&data, cy_rot, data.world.objs->mtx_trans);
	//data.world.objs->mtx_trans = mtx_multiply(&data, cy_rot_y, data.world.objs->mtx_trans);
	//data.world.objs->mtx_trans = mtx_multiply(&data, cy_trans, data.world.objs->mtx_trans);
	//data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);

}
