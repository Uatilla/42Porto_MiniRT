/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_tuples_typ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:48:50 by uviana-a          #+#    #+#             */
/*   Updated: 2024/07/31 19:48:51 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool    is_point(t_tuple tuple)
{
    return(tuple.w == 1);
}

bool    is_vector(t_tuple tuple)
{
    return(tuple.w == 0);
}

bool    is_color(t_tuple tuple)
{
    return(tuple.w == 999999);
}
