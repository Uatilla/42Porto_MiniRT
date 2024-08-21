/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/19 17:12:19 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	render(t_minirt *data);

int	main(void)
{
	t_minirt	data;

	ft_memset(&data, 0, sizeof(data));
	start_mlx(&data.canvas);

	// FLOOR
	t_material m_floor;
	m_floor.color = (t_point){1, 0.9, 0.9, 99999};
	m_floor.ambient = 0.1;
	m_floor.diffuse = 0.7;
	m_floor.specular = 0.2;
	m_floor.shininess = 200;

	t_matrix *floor_scaling;
	floor_scaling = mtx_create(&data, 4, 4);
	fill_idnty_mtx(floor_scaling);
	mtx_scaling(floor_scaling, &(t_point){10, 0.01, 10, 1});

	parse_sphere(&data.world, &m_floor);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, floor_scaling);
	data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);


	// LEFT WALL
	t_material m_left_wall;
	m_left_wall.color = (t_color){1, 0, 0, 99999};
	m_left_wall.ambient = 0.1;
	m_left_wall.diffuse = 0.7;
	m_left_wall.specular = 0.2;
	m_left_wall.shininess = 200;
	
	t_matrix *left_wall_trans;
	left_wall_trans = mtx_create(&data, 4, 4);
	fill_idnty_mtx(left_wall_trans);
	mtx_translation(left_wall_trans, &(t_point){0, 0, 5, 1});

	t_matrix *left_wall_rotation_y;
	left_wall_rotation_y = mtx_create(&data, 4, 4);
	fill_idnty_mtx(left_wall_rotation_y);
	mtx_rotation_y(left_wall_rotation_y, -PI / 4);

	t_matrix *left_wall_rotation_x;
	left_wall_rotation_x = mtx_create(&data, 4, 4);
	fill_idnty_mtx(left_wall_rotation_x);
	mtx_rotation_x(left_wall_rotation_x, PI / 2);

	t_matrix *left_wall_scaling;
	left_wall_scaling = mtx_create(&data, 4, 4);
	fill_idnty_mtx(left_wall_scaling);
	mtx_scaling(left_wall_scaling, &(t_point){10, 0.01, 10, 1});

	parse_sphere(&data.world, &m_left_wall);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, left_wall_trans);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, left_wall_rotation_y);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, left_wall_rotation_x);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, left_wall_scaling);
	data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);


	// RIGHT WALLL
	
	t_material m_right_wall;
	m_right_wall.color = (t_color){0, 0, 1, 99999};
	m_right_wall.ambient = 0.1;
	m_right_wall.diffuse = 0.7;
	m_right_wall.specular = 0.2;
	m_right_wall.shininess = 200;

	t_matrix *right_wall_trans;
	right_wall_trans = mtx_create(&data, 4, 4);
	fill_idnty_mtx(right_wall_trans);
	mtx_translation(right_wall_trans, &(t_point){0, 0, 5, 1});

	t_matrix *right_wall_rotation_y;
	right_wall_rotation_y = mtx_create(&data, 4, 4);
	fill_idnty_mtx(right_wall_rotation_y);
	mtx_rotation_y(right_wall_rotation_y, PI / 4);

	t_matrix *right_wall_rotation_x;
	right_wall_rotation_x = mtx_create(&data, 4, 4);
	fill_idnty_mtx(right_wall_rotation_x);
	mtx_rotation_x(right_wall_rotation_x, PI / 2);

	t_matrix *right_wall_scaling;
	right_wall_scaling = mtx_create(&data, 4, 4);
	fill_idnty_mtx(right_wall_scaling);
	mtx_scaling(right_wall_scaling, &(t_point){10, 0.01, 10, 1});

	parse_sphere(&data.world, &m_right_wall);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, right_wall_trans);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, right_wall_rotation_y);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, right_wall_rotation_x);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, right_wall_scaling);
	data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);


	// MIDDLE SPHERE
	
	t_material middle;
	middle.color = (t_color){0.5, 0.4, 0.5, 99999};
	middle.ambient = 0.1;
	middle.diffuse = 0.7;
	middle.specular = 0.3;
	middle.shininess = 200;

	t_matrix	*middle_tras;
	middle_tras = mtx_create(&data, 4, 4);
	fill_idnty_mtx(middle_tras);
	mtx_translation(middle_tras, &(t_point){-0.5, 1, 0.5, 1});

	parse_sphere(&data.world, &middle);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, middle_tras);
	data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);


	// SMALL SPHERE

	t_material small;
	small.color = (t_color){0.1, 1, 0.5, 99999};
	small.ambient = 0.1;
	small.diffuse = 0.7;
	small.specular = 0.3;
	small.shininess = 200;

	t_matrix	*small_trans;
	small_trans = mtx_create(&data, 4, 4);
	fill_idnty_mtx(small_trans);
	mtx_translation(small_trans, &(t_point){1.5, 0.5, -0.5, 1});

	t_matrix	*small_scaling;
	small_scaling = mtx_create(&data, 4, 4);
	fill_idnty_mtx(small_scaling);
	mtx_scaling(small_scaling, &(t_point){0.5, 0.5, 0.5, 1});

	parse_sphere(&data.world, &small);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, small_trans);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, small_scaling);
	data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);


	t_material smallest;
	smallest.color = (t_color){1, 0.8, 0.1, 99999};
	smallest.ambient = 0.1;
	smallest.diffuse = 0.7;
	smallest.specular = 0.3;
	smallest.shininess = 200;

	t_matrix	*smallest_trans;
	smallest_trans = mtx_create(&data, 4, 4);
	fill_idnty_mtx(smallest_trans);
	mtx_translation(smallest_trans, &(t_point){-1.5, 0.33, -0.75, 1});

	t_matrix	*smallest_scaling;
	smallest_scaling = mtx_create(&data, 4, 4);
	fill_idnty_mtx(smallest_scaling);
	mtx_scaling(smallest_scaling, &(t_point){0.33, 0.33, 0.33, 1});

	parse_sphere(&data.world, &smallest);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, smallest_trans);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, smallest_scaling);
	data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);







	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1}, &data.world);
	data.camera = camera_construct(WIDTH, HEIGTH, PI / 3);
	data.camera.trans = view_transformation(&(t_point){0, 1.5, -5, 1}, &(t_point){0, 1, 0, 1}, &(t_vector){0, 1, 0, 0});
	data.camera.inver = mtx_inverse(&data, data.camera.trans);
	render(&data);
	clean_matrix(&data, data.camera.trans, 0);
	clean_matrix(&data, data.camera.inver, 0);
	clean_world(&data.world);

	return (0);
}

void	render(t_minirt *data)
{
	int			x;
	int			y;

	y = -1;
	while (++y < data->camera.vsize - 1)
	{
		x = -1;
		while (++x < data->camera.hsize - 1)
		{
			data->ray = ray_for_pixel(&data->camera, x, y);
			color_at(data, x, y);
		}
	}
	ft_printf("end render\n");
	mlx_put_image_to_window(data->canvas.mlx, data->canvas.win, data->canvas.img, 0, 0);
	mlx_hook(data->canvas.win, KeyPress, KeyPressMask, handle_key_event, data);
	mlx_loop(data->canvas.mlx);
}
