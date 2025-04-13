/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/13 22:53:08 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H

// Output msgs
# define INVALID_RT	"Invalid file type\n"
# define FILE_NOT_FOUND	"%s: Error opening file\n"
# define UNKNOWN_ELEMENT "%s: Unknown element detected\n"
# define NO_AMBIENCE "%s: No ambience light in file\n"
# define NO_CAMERA "%s: No camera in file\n"
# define NO_LIGHT "%s: No light in file\n"
# define FOV_ERROR "Camera fov out of range\n"
# define POINT_ERROR "Point/Vector incorrectly composed in file\n"
# define COLOR_ERROR "Color incorrectly composed in file\n"
# define MATERIAL_ERROR "Material incorrectly composed in file\n"
# define AMBIENCE_USAGE "Usage: A brithness[0.0,1.0] \
r[0,255],g[0,255],b[0,255]\n"
# define CAMERA_USAGE "Usage: C x,y,z x[-1,1],y[-1,1],z[-1,1] \
fov[0.180]\n"
# define LIGHT_USAGE "Usage: L x,y,z brithness[0.0,1.0] \
r[0,255],g[0,255],b[0,255]\n"
# define SPHERE_USAGE "Usage: sp x,y,z diameter \
r[0,255],g[0,255],b[0,255]\n"
# define PLANE_USAGE "Usage: pl x,y,z x[-1,1],y[-1,1],z[-1,1] \
r[0,255],g[0,255],b[0,255]\n"
# define CYLINDER_USAGE "Usage: cy x,y,z x[-1,1],y[-1,1],z[-1,1] \
diameter height r[0,255],g[0,255],b[0,255]\n"
# define QUAD_USAGE "Usage: qu x,y,z x,y,z x,y,z r[0,255],g[0,255],b[0,255]\n"
# define MULTIPLE_AMBIENCE "Multiple ambience light elements\n"
# define MULTIPLE_CAMERAS "Multiple camera elements\n"
# define MULTIPLE_OBJ_FILES "Multiple object files\n"
# define NO_ARGS "Usage: myprog file\n"
# define NO_SPACE "No more space left in device\n"
# define CLEAN "\r                                                 \r"

// Main miniRT
# define WINDOW_NAME "medium RT"
# define MENU_NAME "MENU"
# define MLX_ERROR 1
# define W 1280
# define H 1024
# define MW 720
# define MH 640
# define EYE_SEPARATION 0.04
# define RAYS_PER_PIXEL 20

//Limits
# define FOV_MIN 0
# define FOV_MAX 180
# define BR_MIN 0
# define BR_MAX 1
# define RGB_MIN 0
# define RGB_MAX 255
# define NV_AXIS_MIN -1
# define NV_AXIS_MAX 1
# define EPSILON 1e-8
# define RED			0x00FF0000
# define YELLOW			0xFFFFFF00
# define GREEN			0x0000FF00
# define CYAN			0x0000FFFF
# define BLUE			0x000000FF
# define MAGENTA		0x00FF00FF
# define WHITE			0x00FFFFFF
# define GRAY			0x00888888
# define ALPHA_WHITE	0xAAAAAAAA
# define BLACK			0x00000000

#endif
