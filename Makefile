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

include mk/parser.mk
include mk/rt.mk

CC = gcc
LIBS = -lft minilibx/libmlx.a #-fsanitize=address
LIBSFOLDERS = -L./libft
vpath %.c $(dir MAKEFILE_LIST)
MLX_FLAG = -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror -flto -O2 -I./includes -I./libft/includes -I./minilibx/
CPPFLAGS += -MMD -MP
OBJDIR = .o
UNAME = $(shell uname)

NAME = RT

OBJS = $(subst .c,.o,$(subst ./srcs/,./$(OBJDIR)/,$(SRCS)))
DEPS = $(subst .c,.d,$(subst ./srcs/,./$(OBJDIR)/,$(SRCS)))

all: $(NAME)

$(NAME): $(OBJS) | lib_rule mlx_rule
	@$(RM) tmp_log
	@$(RM) tmp_errors
	@if  [ -e files_missing ]; then \
		printf "\033[1;31m\n[$(NAME) compilation failed]\033[0m\n"; \
	else \
		$(CC) $(OBJS) -o $(NAME) $(LIBSFOLDERS) $(LIBS) $(MLX_FLAG); \
		printf "\033[1;36m\n[$(NAME) compilation successful]\033[0m\n"; \
	fi;
	@$(RM) files_missing

$(OBJDIR):
	$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/%.o: srcs/%.c | $(OBJDIR)
	@$(shell mkdir -p $(dir $@))
	@printf "%-50s" "Precompiling $(notdir $@)..."
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< 2> ./tmp_log || /usr/bin/touch ./tmp_errors
	@if [ -e tmp_errors ]; then \
		printf "\033[1;31m[KO]\n\033[0m" && /bin/cat 1>&2 ./tmp_log && touch files_missing; \
	elif test -s ./tmp_log; then \
		printf "\033[1;33m[WARNING]\n\033[0m" && /bin/cat ./tmp_log; \
	else \
		printf "\033[1;32m[OK]\n\033[0m"; \
	fi;
	@$(RM) ./tmp_errors

clean:
	@$(MAKE) -C libft clean --no-print-directory
	@$(MAKE) -C minilibx clean --no-print-directory
	@$(RM) $(OBJS) $(DEPS)
	@printf "\033[1;33m[$(NAME) objects files cleaned]\033[0m\n"

fclean:
	@$(MAKE) -C libft fclean --no-print-directory
	@$(MAKE) -C minilibx clean --no-print-directory
	@$(RM) $(OBJS) $(DEPS)
	@printf "\033[1;33m[$(NAME) objects files cleaned]\033[0m\n"
	@$(RM) $(NAME)
	@printf "\033[1;35m[$(NAME) binary deleted]\033[0m\n"

re: fclean all

fclean_nolib:
	@$(RM) $(OBJS) $(DEPS)
	@printf "\033[1;33m[$(NAME) objects files cleaned]\033[0m\n"
	@$(RM) $(NAME)
	@printf "\033[1;35[$(NAME) binary deleted]\033[0m\n"

re_nolib: fclean_nolib all

lib_rule:
	@$(MAKE) -C libft --no-print-directory

mlx_rule:
	@$(MAKE) -C minilibx --no-print-directory

.PHONY: lib_rule all clean fclean re re_nolib fclean_nolib
-include $(DEPS)
