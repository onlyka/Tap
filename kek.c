/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kek.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 19:18:47 by jblythe           #+#    #+#             */
/*   Updated: 2021/04/08 19:19:29 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	kek(int *i, int *j, char **line)
{
	*i = *j;
	while ((*line)[*j] >= '0' && (*line)[*j] <= '9')
		(*j)++;
}

void	kek2(t_all *all, char **tmp)
{
	free(*tmp);
	print_error(all, "Overflow color");
}

void	kek3(char **line, char ***split)
{
	free(*line);
	free_all_arg(split);
}
