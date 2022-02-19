/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:32:31 by jblythe           #+#    #+#             */
/*   Updated: 2021/04/09 16:28:26 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_error(t_all *all, char *line, int j)
{
	if (line[j] != '\0' && line[j] != ' ' && line[j] != ',' && !(line[j]
			>= '0' && line[j] <= '9'))
	{
		printf("line j %c#\n", line[j - 1]);
		print_error(all, "Not valid color");
	}
}

int	color_testing(t_all *all, int i, int j, char **line)
{
	int		rgb[3];
	char	*tmp;
	int		k;

	k = 0;
	while ((*line)[j] != '\0' || (*line)[j] == ' ' || (*line)[j] == ',' ||
	((*line)[j] >= '0' && (*line)[j] <= '9'))
	{
		color_error(all, *line, j);
		if ((*line)[j] >= '0' && (*line)[j] <= '9')
		{
			kek(&i, &j, line);
			tmp = ft_substr((char *)(*line), i, j - i);
			rgb[k++] = ft_atoi((const char *)tmp);
			if (arg_overflow(tmp, 3) == 0 || rgb[k - 1]
				< 0 || rgb[k - 1] > 255)
				kek2(all, &tmp);
			free(tmp);
		}
		else
			j++;
	}
	color_error(all, *line, j);
	return (create_rgb(rgb[0], rgb[1], rgb[2]));
}

int	parse_color(t_all *all, char *line, char symbol)
{
	int		i;
	int		j;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == symbol)
		{
			j = i;
			j++;
			color_error(all, line, j);
			return (color_testing(all, i, j, &line));
		}
		else if (line[i] != ',' && line[i] != ' ' && (line[i] < '0'
				|| line[i] > '9'))
			print_error(all, "Not valid color");
		i++;
	}
	return (0);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
