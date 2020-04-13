
PARSER_PATH = ./srcs/parser/

PARSER =	main.c				\
		fileManager.c			\
		lexer.c				\
		lexerTabInit.c			\
		syntaxAnalysis.c		\
		ast.c				\
		fillStruct.c			\
		valueToStruct.c
	





PARSER_SRCS = $(addprefix $(PARSER_PATH),$(PARSER))
SRCS += $(PARSER_SRCS)
