/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/03 19:15:50 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int main(void)
{

	t_minirt	data;
	t_matrix	*mtx;
	t_matrix	*mtx2;
	t_tuple		tuple_res;
	t_tuple	tup;
	int			x;
	int			y;
    int rows;
    int cols;

	rows = 4;
	cols = 4;
	ft_memset(&data, 0, sizeof(data));
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	start_mlx(&data.canvas);

	mtx = mtx_create(&data, rows, cols);
	mtx_fill(mtx);
	mtx_print(mtx);
	/*mtx2 = mtx_create(&data, rows, cols);
	mtx_fill(mtx2);
	mtx_print(mtx2);*/

	tup.x = 19;
	tup.y = 22;
	tup.z = 13;
	tup.w = 7;
	
	tuple_res = mtx_mult_tuple(mtx, &tup);
	printf("X: %f\n", tuple_res.x);
	printf("Y: %f\n", tuple_res.y);
	printf("Z: %f\n", tuple_res.z);
	printf("W: %f\n", tuple_res.w);
	
	clean_matrix(&data, mtx, 0);
	//clean_matrix(&data, mtx2, 0);

	mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
	mlx_key_hook(data.canvas.win, &handle_key_event, &data);
	mlx_loop(data.canvas.mlx);
	clear_exit(&data, 0);
    return 0;
}
