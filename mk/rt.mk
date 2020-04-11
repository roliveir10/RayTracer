
RT_PATH = ./srcs/rt/

RT = init.c


RT_SRCS = $(addprefix $(RT_PATH),$(RT))
SRCS += $(RT_SRCS)
