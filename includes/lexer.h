#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define NBR_STATE 17
# define NBR_CHAR 128
# define NBR_WORD 25

# define INITIAL_DICO_SIZE 50
# define INCREMENT_DICO_SIZE 25

# define FIRST_WORD_STATE 16
# define LAST_WORD_STATE 40

# define FIRST_OBJECTS_NAME 16
# define LAST_OBJECTS_NAME 19

# define FIRST_STRING_NAME 20
# define LAST_STRING_NAME 22

# define FIRST_VECTOR_NAME 23
# define LAST_VECTOR_NAME 26

# define FIRST_NUMBER_NAME 27
# define LAST_NUMBER_NAME 33

# define FIRST_STRING_VALUE 34
# define LAST_STRING_VALUE 40


int				g_transit[NBR_STATE][NBR_CHAR];
int				g_final[NBR_STATE + 1];

typedef	enum			e_state
{
	START,
	SCBKT,
	SWORD,
	LETTER,
	WORD,
	COLON,
	DIGIT,
	NUMBER,
	POINT,
	FDIGIT,
	COMMA,
	ECBKT,
	SSBKT,
	ESBKT,
	MINUS,
	END,
	SCENE = 16,
	CAMERA,
	LIGHT,
	OBJECTS = 19,
	TYPE = 20,
	TEXTURE,
	NAME = 22,
	ORIGIN = 23,
	ROTATION,
	DIRECTION,
	COLOR = 26,
	AMBIENT = 27,
	SPECULAR,
	ANGLE,
	RADIUS,
	REFLECTION,
	DENSITY,
	TRANSPARENCY = 33,
	LPOINT = 34,
	LCAST,
	LSPOT,
	SSPHERE,
	SCONE,
	SPLAN,
	SCYLINDRE = 40,
	ERROR
}				t_state;

typedef enum			s_symbol
{
	JSON,
	ELEMENT,
	VALUE,
	OBJECT,
	MEMBERS,
	END_MEMBERS,
	MEMBER,
	ARRAY,
	ELEMENTS,
	END_ELEMENTS
}				t_symbol;

typedef struct			s_wordType
{
	char			*lexeme;
	int			type;
}				t_wordType;

typedef struct			s_ast
{
	char			*content;
	int			type;
	struct s_ast		*next;
}				t_ast;

typedef struct			s_error
{
	int			nbrError;
	int			line;
}				t_error;

void				initFinalTab(void);
void				initStateTab(void);

void				lexFile(char *file, t_error *error);
int				*currentState(void);
char				**charSaved(void);

int				syntaxAnalysis(char *file, t_ast **ast);
void				object(char *file, t_error *error, t_ast **ast);

int				isMemberObject(int s);
int				isStringValue(int s);
int				isWord(int symbol);
int				isMemberString(int s);
int				isMemberVector(int s);
int				isMemberNumber(int s);

void				addNoeud(t_ast **ast, char *content, int type);
void				freeAst(t_ast **ast);

#endif
