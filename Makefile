# SRCS				= main_performance.c
SRCS				= main.c \
	setup.c setup_menu.c memory_handle.c \
	anaglyph/anaglyph_aux.c anaglyph/anaglyph.c \
	aux/ft_aux.c aux/general_angle_utils.c aux/general_math_clamps.c \
	aux/general_math_utils.c aux/rgb_aux.c \
	draw/draw_circle.c draw/draw_line.c draw/draw_radio.c draw/draw_rectangule.c \
	menu/hooks_menu.c menu/menu_bt.c menu/menu_ft.c menu/menu_gradients.c \
	menu/menu_help.c menu/menu_material.c menu/menu_quality.c menu/render_bts.c \
	menu/render_menu.c \
	mlx/draw_xpm.c mlx/hooks.c mlx/image_window.c mlx/mlx_aux.c \
	parsing/light_utils.c parsing/object_utils.c parsing/parse_common_elements.c \
	parsing/parse_cone.c parsing/parse_cylinder.c parsing/parse_disk.c \
	parsing/parse_plane.c parsing/parse_quad.c parsing/parse_sphere.c \
	parsing/parser_aux.c parsing/parser.c parsing/parse_lights.c\
	parsing/parse_utils.c parsing/viewport.c \
	rays/antialiasing.c rays/dialectric_scatter.c rays/intersections.c \
	rays/lambertian_scatter.c rays/normals.c rays/ray_color_utils.c \
	rays/ray_color.c rays/bump_scatter.c rays/cone_normal.c rays/intersect_cone.c \
	rays/intersect_cylinder.c rays/get_colors.c\
	rays/ray_utils.c rays/scatter_utils.c rays/specular_scatter.c rays/utils_for_random.c \
	vector/general_vector_utlis.c vector/vec2_basic_operations.c vector/vec2_utils.c \
	vector/vec3_advanced.c vector/vec3_basic_operations.c vector/vec3_utils.c


# find . -type f -name "*.c" -not -path "*/.*" -printf '%P\n' | sort >| sources.txt

SRCS_PATH			=	srcs/
# SRCS				=	$(wildcard $(SRCS_PATH)*.c) $(wildcard $(SRCS_PATH)*/*.c)


NAME 				=	miniRT
CC					=	clang

# this flag exists to prevent conflicting prototype mlx_get_color_value()
ifeq ($(shell hostname), fedora)
	NO_CFLAGS		=	-Wno-deprecated-non-prototype
endif

# CFLAGS				=	-Wall -Wextra -Werror -g -Wno-deprecated-non-prototype $(INCLUDES) $(NO_CFLAGS)
# THREAD_FLAGS				=	-fopenmp -march=native
CFLAGS				=	-Wall -Wextra -Werror -O3 $(INCLUDES) $(THREAD_FLAGS) $(NO_CFLAGS)
#  $(NO_CFLAGS)

SANITIZE			=	-fsanitize=address,undefined
RANDOM_MALLOC		=	-Xlinker --wrap=malloc
AR					=	ar rcs
RM					=	rm -rf


OBJ_DIR				=	objects/
OBJS				=	$(patsubst %.c, $(OBJ_DIR)%.o, $(notdir $(SRCS)))

INCLUDES			=	-I includes/ -I lib/libft/include/ -I lib/mlx_linux/

MLX_PATH			=	lib/mlx_linux/
MLX					=	$(MLX_PATH)libmlx_Linux.a
LIBFT_PATH			=	lib/libft/
LIBFT				=	$(LIBFT_PATH)libft.a
PERSONAL_LIBS		=	-L$(LIBFT_PATH) -lft
MLX_LIBS			=	-L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz -lomp

TOTAL_SRCS			=	$(words $(SRCS))
TOTAL_OBJS			=	$(words $(wildcard $(OBJ_DIR)*))
FILES				=	0

vpath %.c $(SRCS_PATH) $(wildcard $(SRCS_PATH)*/)

$(OBJ_DIR)%.o:		%.c
					@$(CC) $(CFLAGS) -I /usr/local/include -c $< -o $@ && \
					$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
					$(call PRINT_PROGRESS,$(TOTAL_SRCS),$(GRN),$(YELLOW)Compiling$(DEFAULT) $@)

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(LIBFT) $(MLX) $(OBJS)
					@$(CC) $(CFLAGS) $(OBJS) $(PERSONAL_LIBS) $(MLX_LIBS) -o $(NAME)
					@echo -e "\e[2F\e[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\e[E"

sanitize:			$(OBJ_DIR) $(LIBFT) $(MLX) $(OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) $(PERSONAL_LIBS) $(MLX_LIBS) -o $(NAME)
					@echo -e "\e[2F\e[0K$(CYAN)$(NAME)$(DEFAULT) sanitize successfully created\e[E"

random_m:			$(OBJ_DIR) $(LIBFT) $(MLX) $(OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(RANDOM_MALLOC) $(OBJS) $(PERSONAL_LIBS) $(MLX_LIBS) -o $(NAME)
					@echo -e "\e[2F\e[0K$(CYAN)$(NAME)$(DEFAULT) random_m successfully created\e[E"

$(MLX):
					@chmod 777 $(MLX_PATH)configure
					@make -s -C $(MLX_PATH) all

$(LIBFT):
					@make -s -C $(LIBFT_PATH) all

$(OBJ_DIR):
					@mkdir -p $@

clean:
					@$(foreach file,$(wildcard $(OBJ_DIR)*), \
						$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
						$(call PRINT_PROGRESS,$(TOTAL_OBJS),$(RED),$(YELLOW)Deleting$(DEFAULT) $(file)); \
						$(RM) $(file); \
					)
					@if [ -d "$(OBJ_DIR)" ]; then \
						$(RM) $(OBJ_DIR); \
						echo -e "\e[2F\e[0K$(PURPLE)$(OBJ_DIR)$(DEFAULT) deleted\e[E"; \
					fi
					$(eval FILES=0)

fclean:				clean
					@if [ -e "$(LIBFT)" ]; then \
						$(RM) $(LIBFT); \
						echo "$(PURPLE)$(LIBFT)$(DEFAULT) deleted"; \
					fi
					@if [ -e "$(MLX)" ]; then \
						$(RM) $(MLX); \
						echo "$(PURPLE)$(MLX)$(DEFAULT) deleted"; \
					fi
					@if [ -e "$(NAME)" ]; then \
						$(RM) $(NAME); \
						echo "$(PURPLE)$(NAME)$(DEFAULT) deleted"; \
					fi

lcount:
	@printf "$(NAME) has $(BLUE_U)$(shell cat $(SRCS) | wc -l)$(DEFAULT) lines of code\n"
	@printf "There are $(BLUE_U)$(shell cat $(SRCS) | grep if | wc -l) if$(DEFAULT) statements,\
	 $(BLUE_U)$(shell cat $(SRCS) | grep while | wc -l) while$(DEFAULT) loops,\
	 $(BLUE_U)$(shell cat $(SRCS) | grep " = " | wc -l) assigments$(DEFAULT)\n"

re:					fclean all

.PHONY:				all bonus clean fclean re

define PRINT_PROGRESS
	if [ "$(FILES)" -eq "1" ]; then \
		printf "\e[0K$(3)\n["; \
	else \
		printf "\e[0K\e[1F\e[0K$(3)\n["; \
	fi
	@for i in `seq 1 $(shell expr $(FILES) \* 70 / $(1))`; do \
		printf "$(2)=\e[0m"; \
	done
	@for i in `seq 1 $(shell expr 70 - $(FILES) \* 70 / $(1))`; do \
		printf " "; \
	done
	@printf "] $(shell echo $$(($(FILES) * 100 / $(1))))%%"
	if [ "$(FILES)" -eq "$(1)" ]; then \
		printf "\n"; \
	fi
endef

CYAN		=	\e[36m
PURPLE		=	\e[35m
YELLOW		=	\e[33m
GRN			=	\e[32m
RED			=	\e[31m
BLUE_U		=	\e[4;34m
DEFAULT		=	\e[0m

# CYAN				=	\033[36m
# PURPLE				=	\033[35m
# YELLOW				=	\033[33m
# GRN					=	\033[32m
# RED					=	\033[31m
# DEFAULT				=	\033[0m

# @if [ -e "$(GNL)" ]; then \
# 	$(RM) $(GNL); \
# 	echo "$(PURPLE)$(GNL)$(DEFAULT) deleted"; \
# fi
# @if [ -e "$(FT_PRINTF)" ]; then \
# 	$(RM) $(FT_PRINTF); \
# 	echo "$(PURPLE)$(FT_PRINTF)$(DEFAULT) deleted"; \
# fi
