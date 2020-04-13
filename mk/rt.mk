
RT_PATH = ./srcs/rt/

RT =	init.c				\
		keyHandler.c		\
		camera.c			\
		rayHit.c			\
		basicsShape.c		\
		rotationManager.c	\
		basicsNormal.c
	


RT_SRCS = $(addprefix $(RT_PATH),$(RT))
SRCS += $(RT_SRCS)
