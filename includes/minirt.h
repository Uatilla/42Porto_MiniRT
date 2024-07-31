/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:17:41 by uviana-a          #+#    #+#             */
/*   Updated: 2024/07/30 20:17:42 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//LIBRARIES
# include <stdio.h>
# include <stdbool.h>
# include "../libraries/minilibx-linux/mlx.h"
# include "../libraries/libft/libft.h"

//ERROR MESSAGES

//STRUCTURES

typedef struct s_tuple
{
	union
	{
		struct
		{
			float	x;
			float	y;
			float	z;
			float	w;
		};
		struct
		{
			float	r;
			float	g;
			float 	b;
		};
	};
}	t_tuple;

typedef	t_tuple point;
typedef	t_tuple vector;
typedef	t_tuple color;
typedef struct s_minirt
{
	t_tuple     *tuple;
}		t_minirt;
//MACROS

//FUNCTIONS
//tuples
t_tuple creating_tuple(float x, float y, float z, float w);
t_tuple creating_point(float x, float y, float z);
t_tuple creating_vector(float x, float y, float z);
t_tuple creating_color(float r, float g, float b);

bool    is_point(t_tuple tuple);
bool    is_vector(t_tuple tuple);
bool    is_color(t_tuple tuple);


#endif
