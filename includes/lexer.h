#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define NBR_STATE 19
# define NBR_CHAR 128

// number of possible word in the config file
# define NBR_WORD 36

# define FIRST_WORD_STATE 18
# define LAST_WORD_STATE 45

# define FIRST_OBJECTS_NAME 18
# define LAST_OBJECTS_NAME 21

# define FIRST_STRING_NAME 22
# define LAST_STRING_NAME 24

# define FIRST_VECTOR_NAME 25
# define LAST_VECTOR_NAME 29

# define FIRST_NUMBER_NAME 30
# define LAST_NUMBER_NAME 44

# define FIRST_LIMIT_NAME 45
# define LAST_LIMIT_NAME 45

# define FIRST_STRING_VALUE 46
# define LAST_STRING_VALUE 53


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
	COMMENT,
	ENTER,
	END,
	SCENE = 18,
	CAMERA,
	LIGHT,
	OBJECTS = 21,
	TYPE = 22,
	TEXTURE,
	NAME = 24,
	ORIGIN = 25,
	ROTATION,
	BACKGROUND,
	SIZE,
	COLOR = 29,
	AMBIENT = 30,
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
	MAXDISTTOPRINT = 44,
	LIMIT = 45,
	LPOINT = 46,
	LDIR,
	LSPOT,
	SSPHERE,
	SCONE,
	SPLAN,
	SCYLINDRE = 52,
	SBOX = 53,
	ERROR
}						t_state;

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
}						t_symbol;

typedef struct			s_wordType
{
	char				*lexeme;
	int					type;
}						t_wordType;

typedef struct			s_ast
{
	char				*content;
	int					type;
	struct s_ast		*next;
}						t_ast;

typedef struct			s_error
{
	int					nbrError;
	int					line;
}						t_error;

void					initFinalTab(void);
void					initStateTab(void);

void					lexFile(char *file, t_error *error);
int						*currentState(void);
char					**charSaved(void);
char					*stateToWord(int state);

int						syntaxAnalysis(char *file, t_ast **ast);
void						wordCompare(char *charSaved);
void					object(char *file, t_error *error, t_ast **ast);

int						isMemberObject(int s);
int						isStringValue(int s);
int						isWord(int symbol);
int						isMemberString(int s);
int						isMemberVector(int s);
int						isMemberNumber(int s);
int						isMemberLimit(int s);

void					addNoeud(t_ast **ast, char *content, int type);
void					freeAst(t_ast **ast);


// CONVERT VALUE

t_vector				addValueFromVector(t_ast **ast);
t_vector				addValueFromColor(t_ast **ast);
t_vector				addValueFromSize(t_ast **ast);
t_limit					addValueFromLimit(t_ast **ast);
double					addValueFromDouble(char *content);
int					addValueFromInt(char *content);
char					*addValueFromString(char *content);
int					addValueFromLightType(char *toCompare);
int					addValueFromObjectType(char *toCompare);

// FILL STRUCT
int					addValueFromMember(t_ast **ast, int currentObject);

// CHECK STRUCT

int					checkObjectMultiplication(int *object, int currentObject);
int					checkObject(int *object);
int					checkElement(int currentObject, int *element);
#endif
