/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:51:56 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/18 18:23:44 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	sort_intersections(t_xs	*xs, t_intersections *inter)
{
	int	i;

	if (xs->count == 0 || !inter)
		return ;
	xs->arr = ft_calloc(sizeof(*xs->arr), xs->count);
	if (xs->arr == NULL)
		exit(errno);
	i = 0;
	while (inter)
	{
		xs->arr[i++] = inter->t[0];
		xs->arr[i++] = inter->t[1];
		inter = inter->next;
	}
	sort_xs(xs);
}

void	sort_xs(t_xs *xs)
{
	size_t 	i;
	size_t 	j;
	float	temp;

	i = 0;
	while (i < xs->count - 1)
	{
		j = i + 1;
		while (j < xs->count)
		{
			if (xs->arr[j] < xs->arr[i])
			{
				temp = xs->arr[i];
				xs->arr[i] = xs->arr[j];
				xs->arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}
