/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:32:55 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 02:44:05 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_parse_entry	*get_parse_functions(void)
{
	static t_parse_entry	elem_to_parse[] = {
	{"A", parse_ambience},
	{"L", parse_default_light},
	{"C", parse_cam},
	{"sp", parse_sphere},
	{"pl", parse_plane},
	{"cy", parse_cylinder},
	{"qu", parse_quad},
	{"co", parse_cone},
	{"ds", parse_disk},
	};

	return (elem_to_parse);
}

// Choose correct parsing function to parse each different scene element
int	(*parse_scene_elem(char *line))(t_scene *scene, char *line)
{
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
	while (++i < 10)
	{
		if (!ft_strcmp(get_parse_functions()[i].id, tmp))
			return (free(tmp), get_parse_functions()[i].func);
	}
	return (free(tmp), NULL);
}

void	remove_nl(char *line)
{
	int	i;

	i = -1;
	while (line[++i] != '\n')
		;
	line[i] = '\0';
}

// Loop through each line of the given file to gather the information of every
// element
// TODO remove object import logic
int	parser(t_scene *scene, char *file)
{
	char		*line;
	int			file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		return (ft_dprintf(2, FILE_NOT_FOUND, file), 0);
	while (true)
	{
		line = get_next_line(file_fd);
		if (!line)
			return (close(file_fd), 1);
		remove_nl(line);
		if (!parse_scene_elem(line)
			|| !(parse_scene_elem(line)(scene, line)))
			if (line[0] != '\0' && line[0] != '#')
				return (ft_dprintf(2, UNKNOWN_ELEMENT, file),
					free(line), close(file_fd), 0);
		free(line);
	}
}
