# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roliveir <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/28 01:21:35 by roliveir          #+#    #+#              #
#    Updated: 2019/06/23 04:04:07 by oboutrol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		RT
OS		:= $(shell uname)

END			=		\x1b[0m
GREEN		=		\x1b[32m


INC_DIR		=		includes

SDL_LIB		=		SDL2-2.0.9
SDL_DIR		=		SDL2
SDL_TAR		=		$(SDL_LIB).tar.gz
SDL_BUILD	=		$(SDL_DIR)/lib/libSDL2.a

TTF_DIR		=		SDL_text
TTF_BUILD	=		SDL_text/ttf_build/lib
INC_TTF		=		SDL_text/ttf_build/include/SDL2

CC			=		gcc
CPPFLAGS	=		-Ilibft/includes -I$(INC_DIR) -I$(INC_TTF)
CFLAGS		=		-Wall -Werror -Wextra $(shell ./SDL2/bin/sdl2-config --cflags)
LDFLAGS		=		-Llibft -L$(TTF_BUILD) -lft $(shell ./$(SDL_DIR)/bin/sdl2-config --libs) -lSDL2_ttf

ifeq ($(OS),Darwin)
	LDFLAGS += -framework OpenCL
else
	LDFLAGS += -l OpenCL
endif

SRC_DIR		=		srcs
SRC			=						\
parser/main.c						\
parser/fileManager.c				\
parser/lexer.c						\
parser/lexerTabInit.c				\
parser/syntaxAnalysis.c				\
parser/word.c					\
parser/wordReference.c				\
parser/ast.c						\
parser/fillStruct.c					\
parser/convertValue.c				\
parser/valueFromElement.c			\
parser/structValidity.c				\
rt/init.c							\
rt/openCL.c							\
rt/debug.c							\
rt/lib.c							\
rt/loading.c						\
rt/libHook.c						\
rt/keyHandler.c						\
rt/drawWindow.c						\
rt/camera.c							\
rt/utils.c							\
rt/quaternion.c						

SRC_DIR_CL	=		$(SRC_DIR)/rt/ocl/
SRCS_CL		=						\
rth.cl								\
utils.cl							\
quaternion.cl						\
limit.cl							\
normal.cl							\
primitives.cl						\
complexShape.cl						\
debug.cl							\
texture.cl							\
material.cl							\
main.cl								\
initScene.cl

OBJ_DIR		=		.o
OBJ			=		$(SRC:.c=.o)
DEP			=		$(OBJ:.o=.d)

OBJ_FILES	= $(addprefix $(OBJ_DIR)/,$(OBJ))

all: $(NAME)

$(NAME): $(OBJ_FILES) kernel.cl
	$(MAKE) -C libft
	$(CC) $(LDFLAGS) -o $@ $(OBJ_FILES)
	@echo "\n[$(GREEN)$(NAME): Compilation successful$(END)]"

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(TTF_BUILD)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -o $@ -c $<

CL_FILES	=		$(addprefix $(SRC_DIR_CL), $(SRCS_CL))

kernel.cl: $(CL_FILES)
	@printf "Concatenating .cl files: "$@" --> "
	@cat $(CL_FILES) > $@
	@printf "$(GREEN)Concatenating successful$(END)\n"

$(SDL_BUILD): | $(SDL_DIR)
	curl https://www.libsdl.org/release/$(SDL_TAR) --output $(SDL_TAR)
	tar -xf $(SDL_TAR)
	cd $(SDL_LIB) && ./configure --prefix=$(shell pwd)/$(SDL_DIR)
	$(MAKE) -C $(SDL_LIB)
	$(MAKE) -C $(SDL_LIB) install

$(TTF_BUILD): | $(SDL_BUILD)
	cd $(TTF_DIR) && tar -xf freetype-2.8.tar.gz
	cd $(TTF_DIR) && mkdir freetype_build
	cd $(TTF_DIR)/freetype-2.8 && ./configure --prefix=$(shell pwd)/SDL_text/freetype_build
	$(MAKE) -C $(TTF_DIR)/freetype-2.8
	export PKG_CONFIG_PATH=$(shell pwd)/SDL_text/freetype-2.8/builds/unix
	$(MAKE) -C $(TTF_DIR)/freetype-2.8 install
	cd $(TTF_DIR) && unzip SDL2_ttf-2.0.15.zip 
	mkdir $(TTF_DIR)/ttf_build
	cd $(TTF_DIR)/SDL2_ttf-2.0.15 && FT2_CONFIG="$(shell pwd)/SDL_text/freetype_build/bin/freetype-config" SDL2_CONFIG="$(shell pwd)/SDL2/bin/sdl2-config" ./configure --prefix="$(shell pwd)/SDL_text/ttf_build"
	$(MAKE) -C $(TTF_DIR)/SDL2_ttf-2.0.15
	$(MAKE) -C $(TTF_DIR)/SDL2_ttf-2.0.15 install

$(SDL_DIR):
	@mkdir $@ 2> /dev/null || true

$(OBJ_DIR):
	@mkdir $@ 2> /dev/null || true
	@mkdir $@/parser 2> /dev/null || true
	@mkdir $@/rt 2> /dev/null || true

clean:
	$(MAKE) -C libft clean --no-print-directory
	$(RM) $(SDL_TAR)
	$(RM) -r $(SDL_LIB)
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(TTF_DIR)/freetype-2.8
	$(RM) -r $(TTF_DIR)/SDL2_ttf-2.0.15
	$(RM) -f kernel.cl
	@echo "$(GREEN)[$(NAME) objects files cleaned]$(END)"
	@echo "$(GREEN)[$(SDL_LIB) files removed]$(END)"
	@echo "$(GREEN)[$(TTF_DIR) files removed]$(END)"
	@echo "$(GREEN)[kernel.cl file removed]$(END)"

fclean: clean
	$(MAKE) -C libft fclean --no-print-directory
	$(RM) $(NAME)
	$(RM) -r $(SDL_DIR)
	$(RM) -r $(TTF_DIR)/freetype_build
	$(RM) -r $(TTF_DIR)/ttf_build
	@echo "$(GREEN)[$(NAME) binary deleted]$(END)"

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean
