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

void	mtx_fill_value(t_matrix *mtx)
{
	mtx->mtx[0][0] = 3;
	mtx->mtx[0][1] = -9;
	mtx->mtx[0][2] = 7;
	mtx->mtx[0][3] = 3;

	mtx->mtx[1][0] = 3;
	mtx->mtx[1][1] = -8;
	mtx->mtx[1][2] = 2;
	mtx->mtx[1][3] = -9;

	mtx->mtx[2][0] = -4;
	mtx->mtx[2][1] = 4;
	mtx->mtx[2][2] = 4;
	mtx->mtx[2][3] = 1;

	mtx->mtx[3][0] = -6;
	mtx->mtx[3][1] = 5;
	mtx->mtx[3][2] = -1;
	mtx->mtx[3][3] = 1;
}

void	mtx_fill_value_b(t_matrix *mtx)
{
	mtx->mtx[0][0] = 8;
	mtx->mtx[0][1] = 2;
	mtx->mtx[0][2] = 2;
	mtx->mtx[0][3] = 2;

	mtx->mtx[1][0] = 3;
	mtx->mtx[1][1] = -1;
	mtx->mtx[1][2] = 7;
	mtx->mtx[1][3] = 0;

	mtx->mtx[2][0] = 7;
	mtx->mtx[2][1] = 0;
	mtx->mtx[2][2] = 5;
	mtx->mtx[2][3] = 4;

	mtx->mtx[3][0] = 6;
	mtx->mtx[3][1] = -2;
	mtx->mtx[3][2] = 0;
	mtx->mtx[3][3] = 5;
}

int main(void)
{

	t_minirt	data;
	t_matrix	*mtx_a;
	t_matrix	*mtx_a_inv;
	t_matrix	*mtx_res;


	float	determ_a;
	float	determ_a_inv;

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

	printf("\n=======MATRIX A======\n");
	mtx_a = mtx_create(&data, rows, cols);
	mtx_fill_value(mtx_a);
	mtx_print(mtx_a);
	determ_a = determinant(&data, mtx_a);
	printf("Determ A: %f\n", determ_a);

	printf("\n=======MATRIX A (inverse)======\n");

	mtx_a_inv = mtx_inverse(&data, mtx_a);
	mtx_print(mtx_a_inv);
	determ_a_inv = determinant(&data, mtx_a_inv);
	printf("Determ A (inverse): %f\n", determ_a_inv);

	printf("\n=======MATRIX A * A(inverse)======\n");
	mtx_res = mtx_multiply(&data, mtx_a, mtx_a_inv);
	mtx_print(mtx_res);


	clean_matrix(&data, mtx_a, 0);
	clean_matrix(&data, mtx_a_inv, 0);
	clean_matrix(&data, mtx_res, 0);

	mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
	mlx_key_hook(data.canvas.win, &handle_key_event, &data);
	mlx_loop(data.canvas.mlx);
	clear_exit(&data, 0);
    return 0;
}
