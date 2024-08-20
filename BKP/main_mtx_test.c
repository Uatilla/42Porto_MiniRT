/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/10 21:49:33 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


void	mtx_fill_a(t_matrix *mtx)
{
	mtx->mtx[0][0] = 1;
	mtx->mtx[0][1] = 2;
	mtx->mtx[0][2] = 3;
	mtx->mtx[0][3] = 4;

	mtx->mtx[1][0] = 2;
	mtx->mtx[1][1] = 4;
	mtx->mtx[1][2] = 4;
	mtx->mtx[1][3] = 2;

	mtx->mtx[2][0] = 8;
	mtx->mtx[2][1] = 6;
	mtx->mtx[2][2] = 4;
	mtx->mtx[2][3] = 1;

	mtx->mtx[3][0] = 0;
	mtx->mtx[3][1] = 0;
	mtx->mtx[3][2] = 0;
	mtx->mtx[3][3] = 1;
}

void	mtx_fill_b(t_matrix *mtx)
{
	mtx->mtx[0][0] = -2;
	mtx->mtx[0][1] = 1;
	mtx->mtx[0][2] = 2;
	mtx->mtx[0][3] = 3;

	mtx->mtx[1][0] = 3;
	mtx->mtx[1][1] = 2;
	mtx->mtx[1][2] = 1;
	mtx->mtx[1][3] = -1;

	mtx->mtx[2][0] = 4;
	mtx->mtx[2][1] = 3;
	mtx->mtx[2][2] = 6;
	mtx->mtx[2][3] = 5;

	mtx->mtx[3][0] = 1;
	mtx->mtx[3][1] = 2;
	mtx->mtx[3][2] = 7;
	mtx->mtx[3][3] = 8;
}



// nao esquecer de chamar ft_memeset para data;
// nao esquecer de setar a origem da camera(ray) e depois a direcao;
// importante chamar clear_ray_inter depoins de check intersection;
// comecar com start_mlx, e nao esquecer de chamar no fim:
// 		mlx_put_image_to_window e mlx_loop
int	main(int argc, char **argv)
{
	t_minirt	data;
	int			x;
	int			y;
	int			fd;
	float		w_x;
	float		w_y;


	t_matrix	*mtx_a;
	t_matrix	*mtx_b;
	t_matrix	*mtx_res;
	t_tuple		pt_vec;
	t_tuple		res;


	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(data));
	/*fd = chk_input(argc, argv[1]);
	parse_objects(SP, &data, fd);
	mtx_scaling(((t_sphere *)data.objs)->mtx_trans, &(t_point){0.5,0.5,0.5,69});
	((t_sphere *)data.objs)->mtx_inver = mtx_inverse(&data, ((t_sphere *)data.objs)->mtx_trans);
	start_mlx(&data.canvas);
	data.ray.origin = (t_point){0, 0, -5, 1};
	y = -1;
	while (++y < HEIGTH)
	{
		x = -1;
		while (++x < WIDTH)
		{
			w_x = map_x(x, -5, 5);		
			w_y = map_y(y, -5, 5);		
			check_intersections(&data, &(t_point){w_x, w_y, 5, 1});
			if (data.first_hit)
			{
				write_pixel(&data.canvas, x, y, &(t_color){1, 0, 0, 69});
			}
			clear_ray_inter(&data);
		}
	}
	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0, 0);
	mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
	mlx_key_hook(data.canvas.win, &handle_key_event, &data);
	mlx_loop(data.canvas.mlx);*/
	
	pt_vec = creating_point(1, 2, 3);

	mtx_a = mtx_create(NULL, 4, 4);
	mtx_fill_a(mtx_a);
	mtx_print(mtx_a);
	printf("=========================\n");
	/*mtx_b = mtx_create(NULL, 4, 4);
	mtx_fill_b(mtx_b);
	mtx_print(mtx_b);
	printf("=========================\n");
	mtx_res = mtx_multiply(NULL, mtx_a, mtx_b);
	mtx_print(mtx_res);*/

	res = mtx_mult_tuple(mtx_a, &pt_vec);
	printf("X:%f Y:%f Z:%f W:%f \n", res.x, res.y, res.z, res.w);
	printf("=========================\n");
	clean_matrix(NULL, mtx_a, 0);
	//clean_matrix(NULL, mtx_b, 0);
	//clean_matrix(NULL, mtx_res, 0);
	clear_exit(&data, 0);
}
