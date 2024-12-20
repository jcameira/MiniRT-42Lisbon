# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:12:04 by cjoao-de          #+#    #+#              #
#    Updated: 2024/12/20 17:43:47 by cjoao-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Pretty colors
include include/pretty_colors_ANSI

# Project files
#
SRC =	ft_isalpha.c	ft_isdigit.c	ft_tolower.c	ft_isalnum.c \
		ft_isascii.c	ft_isprint.c	ft_toupper.c	ft_strchr.c \
		ft_strrchr.c	ft_strlen.c		ft_strncmp.c	ft_memset.c \
		ft_bzero.c		ft_memchr.c		ft_memcpy.c		ft_memcmp.c \
		ft_strnstr.c	ft_strlcpy.c	ft_strlcat.c 	ft_atoi.c \
		ft_calloc.c		ft_strdup.c 	ft_putchar_fd.c	ft_itoa.c\
		ft_substr.c		ft_strjoin.c	ft_strtrim.c	ft_strmapi.c\
		ft_putstr_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c	ft_striteri.c \
		ft_memmove.c	ft_split.c 		ft_isspace.c	ft_atol.c \
		ft_issignal.c 	ft_abs.c		ft_ismax.c		ft_atof.c \
		ft_itoa_addr.c	ft_ftoa.c		ft_ftoa_addr.c	ft_fabs.c \
		ft_fabsf.c 		ft_strcmp.c		ft_free_dptr.c	ft_memset_float.c \
		ft_printf.c		ft_printf_format.c \
		get_next_line.c	get_next_line_utils.c \
		ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c	ft_lstlast.c \
		ft_lstadd_back.c	ft_lstdelone.c	ft_lstclear.c	ft_lstiter.c \
		ft_lstmap.c
SRC_DIR = ./source/
OBJ_DIR = ../../objects/
INC_DIR = ./include/
OBJECTS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Build settings
#
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I $(INC_DIR)
debug: CFLAGS += -g3 -fPIE -O0
MAKEFLAGS += --no-print-directory #  --silent
.SILENT:  clean fclean debug $(OBJECTS) $(NAME)
ARFLAGS = rvs
RM = rm -rf
CC = cc
AR = ar rcs

TOTAL_SRCS			=	$(words $(SRC))
TOTAL_OBJS			=	$(words $(wildcard $(OBJ_DIR)*))
FILES				=	0

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ && \
					$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
					$(call PRINT_PROGRESS,$(TOTAL_SRCS),$(GRN),$(YELLOW)Compiling$(DEFAULT) $@)

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(OBJECTS)
					@$(AR) $(NAME) $(OBJECTS)
					@echo -e "\e[2F\e[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\e[E"

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)

clean:
					@$(foreach file,$(wildcard $(OBJ_DIR)*), \
						$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
						$(call PRINT_PROGRESS,$(TOTAL_OBJS),$(RED),$(YELLOW)Deleting$(DEFAULT) $(file)); \
						$(RM) $(file); \
					)
					$(eval FILES=0)

fclean:				clean
					@if [ -e "$(NAME)" ]; then \
						$(RM) $(NAME); \
						echo "$(PURPLE)$(NAME)$(DEFAULT) deleted"; \
					fi

re:					fclean all

.PHONY:				all clean fclean re

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
YELLOW				=	\e[33m
GRN					=	\e[32m
RED					=	\e[31m
DEFAULT				=	\e[0m
