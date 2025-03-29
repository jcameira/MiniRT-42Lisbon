NAME 				=	miniRT

CC					=	clang
NO_CFLAGS			=	-Wno-deprecated-non-prototype
CFLAGS				=	-Wall -Wextra -Werror -g $(NO_CFLAGS) $(INCLUDES)

# CFLAGS				=	-Wall -Wextra -Werror -O3 $(INCLUDES)
SANITIZE			=	-fsanitize=address,undefined
RANDOM_MALLOC		=	-Xlinker --wrap=malloc
AR					=	ar rcs
RM					=	rm -rf

SRCS_PATH			=	srcs/
#SRCS_PATH			=	srcs_refactor/
SRCS				=	$(wildcard $(SRCS_PATH)*.c) $(wildcard $(SRCS_PATH)*/*.c)

OBJ_DIR				=	objects/
OBJS				=	$(patsubst %.c, $(OBJ_DIR)%.o, $(notdir $(SRCS)))

INCLUDES			=	-I includes/ -I lib/libft/include/ -I lib/mlx_linux/

MLX_PATH			=	lib/mlx_linux/
MLX					=	$(MLX_PATH)libmlx_Linux.a
LIBFT_PATH			=	lib/libft/
LIBFT				=	$(LIBFT_PATH)libft.a
PERSONAL_LIBS		=	-L$(LIBFT_PATH) -lft
MLX_LIBS			=	-L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz

TOTAL_SRCS          =   $(words $(SRCS))
TOTAL_OBJS          =   $(words $(wildcard $(OBJ_DIR)*))
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
					@$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) $(PERSONAL_LIBS) $(OTHER_LIBS) -o $(NAME)
					@echo -e "\e[2F\e[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\e[E"

random_m:			$(OBJ_DIR) $(LIBFT) $(MLX) $(OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(RANDOM_MALLOC) $(OBJS) $(PERSONAL_LIBS) $(OTHER_LIBS) -o $(NAME)
					@echo -e "\e[2F\e[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\e[E"

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

CYAN				=	\e[36m
PURPLE				=	\e[35m
YELLOW				=	\e[33m
GRN					=	\e[32m
RED					=	\e[31m
DEFAULT				=	\e[0m

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
