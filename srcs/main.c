/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/07/30 20:02:46 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int main()
{
    point   p;
    vector  v;
    color   c;

    p = creating_point(1, 2, 3);
    printf("Result: %d\n", is_point(p));
    printf("----------------\n");
    v = creating_vector(2, 3, 4);
    printf("Result: %d\n", is_vector(v));
    printf("----------------\n");
    c = creating_color(200, 113, 134);
    printf("Result: %d\n", is_color(c));
    return (0);
}
