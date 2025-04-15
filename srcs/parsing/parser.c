/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:32:55 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/15 20:17:17 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Choose correct parsing function to parse each different scene element
int	(*parse_scene_elem(char *line))(t_scene *scene, char *line)
{
	static void	*elem_to_parse[8][2] = {
	{"A", parse_ambience},
	{"L", parse_default_light},
	{"C", parse_cam},
	{"sp", parse_sphere},
	{"pl", parse_plane},
	{"cy", parse_cylinder},
	//{"qu", parse_quad},
	//{"co", parse_cone},
	//{"ds", parse_disk},
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
	while (++i < 5)
	{
		if (!ft_strcmp(elem_to_parse[i][0], tmp))
			return (free(tmp), elem_to_parse[i][1]);
	}
	return (free(tmp), NULL);
}

// Loop through each line of the given file to gather the information of every
// element
// TODO remove object import logic
int	parser(t_scene *scene, char *file)
{
	char		*line;
	char		*line_no_nl;
	int			file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		return (ft_dprintf(2, FILE_NOT_FOUND, file), 0);
	while (true)
	{
		line = get_next_line(file_fd);
		if (!line)
			return (close(file_fd), 1);
		line_no_nl = ft_strtrim(line, "\n");
		if (!line_no_nl)
			return (close(file_fd), free(line), 1);
		free(line);
		if (parse_scene_elem(line_no_nl))
		{
			if (!(parse_scene_elem(line_no_nl)(scene, line_no_nl)))
				return (free(line_no_nl), close(file_fd), 0);
		}
		else if (line_no_nl[0] != '\0' && line_no_nl[0] != '#')
			return (ft_dprintf(2, UNKNOWN_ELEMENT, file), free(line_no_nl), close(file_fd), 0);
		free(line_no_nl);
	}
	close(file_fd);
}
