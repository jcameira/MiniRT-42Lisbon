NAME 				=	miniRT

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g -I $(INCLUDES)
SANITIZE			=	-fsanitize=address,undefined
RANDOM_MALLOC		=	-Xlinker --wrap=malloc
AR					=	ar rcs
RM					=	rm -rf

SRCS				=	main.c #malloc.c
SRCS_PATH			=	srcs/

OBJ_DIR				=	objects/
OBJS				=	$(SRCS:%.c=$(OBJ_DIR)%.o)
ALL_OBJS			=	$(OBJ_DIR)*.o

INCLUDES			=	includes/

MLX_PATH			=	lib/mlx_linux/
MLX					=	$(MLX_PATH)libmlx_Linux.a
LIBFT_PATH			=	lib/libft/
LIBFT				=	$(LIBFT_PATH)libft.a
PERSONAL_LIBS		=	-L$(LIBFT_PATH) -lft
MLX_LIBS			=	-L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz

TOTAL_SRCS          =   $(words $(SRCS))
TOTAL_OBJS          =   $(words $(wildcard $(OBJ_DIR)*))
FILES				=	0

$(OBJ_DIR)%.o:		$(SRCS_PATH)%.c
					@$(CC) $(CFLAGS) -I /usr/local/include -c $< -o $@ && \
					$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
					$(call PRINT_PROGRESS,$(TOTAL_SRCS),$(GRN),$(YELLOW)Compiling$(DEFAULT) $@)

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(LIBFT) $(MLX) $(OBJS)
					@$(CC) $(CFLAGS) $(OBJS) $(PERSONAL_LIBS) $(MLX_LIBS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

sanitize:			$(OBJ_DIR) $(LIBFT) $(MLX) $(OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) $(PERSONAL_LIBS) $(OTHER_LIBS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

random_m:			$(OBJ_DIR) $(LIBFT) $(GNL) $(FT_PRINTF) $(MLX) $(OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(RANDOM_MALLOC) $(OBJS) $(PERSONAL_LIBS) $(OTHER_LIBS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

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
						echo "\033[2F\033[0K$(PURPLE)$(OBJ_DIR)$(DEFAULT) deleted\033[E"; \
					fi
					$(eval FILES=0)

fclean:				clean
					@if [ -e "$(LIBFT)" ]; then \
						$(RM) $(LIBFT); \
						echo "$(PURPLE)$(LIBFT)$(DEFAULT) deleted"; \
					fi
					@if [ -e "$(GNL)" ]; then \
						$(RM) $(GNL); \
						echo "$(PURPLE)$(GNL)$(DEFAULT) deleted"; \
					fi
					@if [ -e "$(FT_PRINTF)" ]; then \
						$(RM) $(FT_PRINTF); \
						echo "$(PURPLE)$(FT_PRINTF)$(DEFAULT) deleted"; \
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
        printf "\033[0K$(3)\n["; \
    else \
        printf "\033[0K\033[1F\033[0K$(3)\n["; \
    fi
    @for i in `seq 1 $(shell expr $(FILES) \* 70 / $(1))`; do \
        printf "$(2)=\033[0m"; \
    done
    @for i in `seq 1 $(shell expr 70 - $(FILES) \* 70 / $(1))`; do \
        printf " "; \
    done
    @printf "] $(shell echo $$(($(FILES) * 100 / $(1))))%%"
	if [ "$(FILES)" -eq "$(1)" ]; then \
        printf "\n"; \
	fi
endef

CYAN				=	\033[36m
PURPLE				=	\033[35m
YELLOW				=	\033[33m
GRN					=	\033[32m
RED					=	\033[31m
DEFAULT				=	\033[0m
