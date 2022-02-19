/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 19:33:17 by jblythe           #+#    #+#             */
/*   Updated: 2021/04/12 18:32:15 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	path_parsing(t_all *all, char *line, char **f_path, int c)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (ft_strncmp(&line[i], "NO ", c, 1) == 0 || ft_strncmp(&line[i],
			"SO ", c, 1) == 0 || ft_strncmp(&line[i],
			"WE ", c, 1) == 0 || ft_strncmp(&line[i],
			"EA ", c, 1) == 0 || ft_strncmp(&line[i], "S ", c, 1) == 0)
	{
		i += c;
		path = ft_substr((const char *)line, i, ft_strlen((char *)line) - i);
		i = ft_strlen((char *)line);
		while (line[i] == ' ')
			i--;
		if (line[i - 1] != 'm' || line[i - 2] != 'p' || line[i - 3]
			!= 'x' || line[i - 4] != '.')
		{
			free(path);
			print_error(all, "Not correct path");
		}
		else
			*f_path = path;
	}
}

void	free_all_arg(char ***line)
{
	int	i;

	i = 0;
	if (**line != NULL)
	{
		while (i < get_arg_count(*line))
			free((*line)[i++]);
	}
	free(*line);
}

int	open_cub(t_all *all, char *path)
{
	int	fd;
	int	len;

	len = ft_strlen((char *)path);
	fd = open(path, O_RDONLY);
	if (fd < 0 || path[len - 1] != 'b' || path[len - 2]
		!= 'u' || path[len - 3] != 'c' || path[len - 4] != '.')
		print_error(all, "Not correct cub file");
	return (fd);
}
