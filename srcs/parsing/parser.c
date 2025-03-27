/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:32:55 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/25 13:00:53 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Choose correct parsing function to parse each different scene element
int	(*parse_scene_elem(char *line))(t_scene *scene, char *line)
{
	static void	*elem_to_parse[6][2] = {
	{"A", parse_ambience},
	{"L", parse_light},
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
	while (++i < 6)
	{
		if (!ft_strcmp(elem_to_parse[i][0], tmp))
			return (free(tmp), elem_to_parse[i][1]);
	}
	return (free(tmp), NULL);
}

// Loop through each line of the given file to gather the information of every
// element
int	parser(t_scene *scene, t_camera *cam, char *file)
{
	char		*line;
	int			file_fd;
	int			obj_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		return (ft_dprintf(2, FILE_NOT_FOUND, file), 0);
	while (true)
	{
		line = get_next_line(file_fd);
		if (!line)
			return (1);
		if (line[0] == 'C' && (line[1] == 9 || line[1] == 32))
		{
			if (!parse_cam(cam, line))
				return (ft_dprintf(2, CAMERA_USAGE), free(line), 0);
		}
		else if (parse_scene_elem(line))
		{
			if (!(parse_scene_elem(line)(scene, line)))
				return (free(line), 0);
		}
		else if (line[0] == 'F' && (line[1] == 9 || line[1] == 32))
		{
			if (getenv("TERM_PROGRAM") != NULL)	// test for vscode debugging
				obj_fd = open("/home/kajo/42/miniRT/scenes/dragon_obj.rt", O_RDONLY);	// from debugger
			else
				obj_fd = open("scenes/dragon_obj.rt", O_RDONLY); // from terminal
			if (obj_fd < 0)
				return (ft_dprintf(2, FILE_NOT_FOUND, "scenes/dragon_obj.rt"), 0);
			parse_object(scene, obj_fd);
			// return (parse_object(obj_fd), 0);
		}
		else if (line[0] != '\n')
			return (ft_dprintf(2, UNKNOWN_ELEMENT, file), free(line), 0);
		free(line);
	}
	close(file_fd);
}
