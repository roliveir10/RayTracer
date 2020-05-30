#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "cl.h"

# define NBR_STATE 19
# define NBR_CHAR 128

// number of possible word in the config file
# define NBR_WORD 53

# define FIRST_WORD_STATE 18
# define LAST_WORD_STATE 45

# define FIRST_OBJECTS_NAME 18
# define LAST_OBJECTS_NAME 20

# define FIRST_STRING_NAME 21
# define LAST_STRING_NAME 25

# define FIRST_VECTOR_NAME 26
# define LAST_VECTOR_NAME 33

# define FIRST_NUMBER_NAME 33
# define LAST_NUMBER_NAME 42

# define FIRST_STRING_VALUE 43
# define LAST_STRING_VALUE 70


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
	OBJECTS = 20,
	TYPE = 21,
	MATERIAL,
	PATTERN,
	BUMPTYPE,
	NAME = 25,
	ORIGIN = 26,
	ROTATION,
	BACKGROUND,
	COLOR,
	SCALE,
	LIMITMIN,
	LIMITMAX,
	REFRAC = 33,
	SHININESS,
	INTENSITY,
	SCREENX,
	SCREENY,
	FOV,
	SAMPLERATE,
	MAXDISTTOPRINT,
	BOUNCEMAX,
	OPACITY = 42,
	SSPHERE = 43,
	SCONE,
	SPLAN,
	SCYLINDRE,
	SCUBE,
	SDISK,
	SHYPERBOLOID,
	SINFHYPERBOLOID,
	SINFCYLINDRE,
	SINFCONE,
	SRECTANGLE,
	STRIANGLE,
	SPARABOLOID,
	SSADDLE,
	STHORUS,
	SCAPSULE,
	SELLIPSOID,
	SROUNDEDCONE,
	SSPHERE4,
	SGOURSAT,
	SROUNDEDBOX,
	SLIGHT,
	SDIFFUSE,
	STRANSPARENT,
	SSPECULAR,
	SSOLID,
	SFLAT,
	SBUMP = 69,
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

typedef struct			s_limit
{
	cl_float3			origin;
	cl_float3			size;
}						t_limit;

char					*open_file(char *argv);
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

void					addNoeud(t_ast **ast, char *content, int type);
void					freeAst(t_ast **ast);


// CONVERT VALUE

cl_float3				addValueFromVector(t_ast **ast);
cl_float3				addValueFromRotation(t_ast **ast);
cl_float3				addValueFromColor(t_ast **ast);
double					addValueFromDouble(char *content);
int						addValueFromInt(char *content);
int						addValueFromPrimitiveType(char *toCompare);
int						addValueFromMaterialType(char *toCompare);
int						addValueFromPatternType(char *toCompare);
int						addValueFromBumpType(char *toCompare);

// FILL STRUCT
int						fillStruct(t_ast *ast);
int						addValueFromMember(t_ast **ast, int currentObject);

// CHECK STRUCT

int						checkObjectMultiplication(int *object, int currentObject);
int						checkObject(int *object);
int						checkElement(void);
#endif
