/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_temp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:32:12 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/13 11:32:16 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//FUNCAO TEMPORARIA APENAS PARA FINS DE TESTE!!
void	mtx_fill(t_matrix *mtx)
{
	int	value;
	int	i;
	int	j;

	value = 17;
	i = -1;
	while (++i < mtx->rows)
	{
		j = -1;
		while (++j < mtx->cols)
		{
			mtx->mtx[i][j] = value++;
		}
	}
}

void	mtx_print(t_matrix *mtx)//FUNCAO TEMPORARIA APENAS PARA FINS DE TESTE!!
{
	int	value;
	int	i;
	int	j;

	value = 0;
	i = -1;
	while (++i < mtx->rows)
	{
		j = -1;
		while (++j < mtx->cols)
		{
			printf("%f | ", mtx->mtx[i][j]);
		}
		printf("\n");
	}
}
