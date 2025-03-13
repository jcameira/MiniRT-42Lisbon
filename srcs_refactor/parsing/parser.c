/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:32:55 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/12 13:11:09 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Choose correct parsing function to parse each different scene element
int	(*parse_scene_elem(char *line))(t_scene *scene, char *line)
{
	static void	*elem_to_parse[7][2] = {
	{"A", parse_ambience},
	{"L", parse_light},
	{"C", parse_cam},
	{"sp", parse_sphere},
	{"pl", parse_plane},
	{"cy", parse_cylinder},
	{"qu", parse_quad},
	};
	char		*tmp;
	int			i;

	tmp = ft_strdup(line);
	if (!tmp)
		return (ft_dprintf(2, NO_SPACE), NULL);
	i = 0;
	while (ft_isalpha(tmp[i]))
		i++;
	tmp[i] = '\0';
	i = -1;
	while (++i < 7)
	{
		if (!ft_strcmp(elem_to_parse[i][0], tmp))
			return (free(tmp), elem_to_parse[i][1]);
	}
	return (free(tmp), NULL);
}

// Loop through each line of the given file to gather the information of every
// element
int	parser(t_scene *scene, char *file)
{
	char		*line;
	int			file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		return (ft_dprintf(2, FILE_NOT_FOUND, file), close(file_fd), 0);
	while (true)
	{
		line = get_next_line(file_fd);
		if (!line)
			return (close(file_fd), 1);
		if (parse_scene_elem(line))
		{
			if (!(parse_scene_elem(line)(scene, line)))
				return (free(line), close(file_fd), 0);
		}
		else if (line[0] != '\n')
			return (ft_dprintf(2, UNKNOWN_ELEMENT, file), free(line), close(file_fd), 0);
		free(line);
	}
}
