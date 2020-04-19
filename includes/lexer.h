#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define NBR_STATE 17
# define NBR_CHAR 128

// number of possible word in the config file
# define NBR_WORD 34

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
# define LAST_NUMBER_NAME 42

# define FIRST_STRING_VALUE 43
# define LAST_STRING_VALUE 49


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
	BACKGROUND,
	COLOR = 26,
	AMBIENT = 27,
	SPECULAR,
	ANGLE,
	RADIUS,
	REFLECTION,
	DENSITY,
	TRANSPARENCY,
	SHININESS,
	SHININESSSTRENGTH,
	INTENSITY,
	SCREENX,
	SCREENY,
	FOV,
	SAMPLERATE,
	PIXPERUNIT,
	MAXDISTTOPRINT = 42,
	LPOINT = 43,
	LDIR,
	LSPOT,
	SSPHERE,
	SCONE,
	SPLAN,
	SCYLINDRE = 49,
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

void				addValueToStruct(char *content, int currentObject, int currentName, int vcount);
#endif
