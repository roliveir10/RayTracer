#include "lexer.h"

void			initFinalTab(void)
{
	for (int i = 0; i < NBR_STATE; i++)
		g_final[i] = 0;
	g_final[1] = SCBKT + 1;
	g_final[4] = WORD + 1;
	g_final[5] = COLON + 1;
	g_final[7] = -(NUMBER + 1);
	g_final[10] = COMMA + 1;
	g_final[11] = ECBKT + 1;
	g_final[12] = SSBKT + 1;
	g_final[13] = ESBKT + 1;
	g_final[15] = END + 1;
	g_final[NBR_STATE] = ERROR + 1;
}

void			initStateTab(void)
{
	int		i;
	int		j;

	for (i = 0; i < NBR_STATE; i++)
		for (j = 0; j < NBR_CHAR; j++)
			g_transit[i][j] = NBR_STATE;
	for (j = 9; j <= 32; j++)
		g_transit[0][j] = 0;
	g_transit[0][0] = 15;
	g_transit[0]['"'] = 2;
	g_transit[0][':'] = 5;
	g_transit[0]['{'] = 1;
	g_transit[0]['}'] = 11;
	g_transit[0][','] = 10;
	g_transit[0]['['] = 12;
	g_transit[0][']'] = 13;
	g_transit[0]['-'] = 14;
	for (j = '0'; j <= '9'; j++)
		g_transit[0][j] = 6;

	for (j = 'A'; j <= 'Z'; j++)
		g_transit[2][j] = 3;
	for (j = 'a'; j <= 'z'; j++)
		g_transit[2][j] = 3;
	g_transit[2]['"'] = 4;

	g_transit[3]['"'] = 4;
	for (j = 'A'; j <= 'Z'; j++)
		g_transit[3][j] = 3;
	for (j = 'a'; j <= 'z'; j++)
		g_transit[3][j] = 3;

	for (j = 9; j <= 32; j++)
		g_transit[6][j] = 7;
	g_transit[6]['{'] = 7;
	g_transit[6][','] = 7;
	g_transit[6]['.'] = 8;
	g_transit[6][']'] = 7;
	for (j = '0'; j <= '9'; j++)
		g_transit[6][j] = 6;

	for (j = '0'; j <= '9'; j++)
		g_transit[8][j] = 9;

	for (j = 9; j <= 32; j++)
		g_transit[9][j] = 7;
	g_transit[9]['}'] = 7;
	g_transit[9][','] = 7;
	g_transit[9][']'] = 7;
	for (j = '0'; j <= '9'; j++)
		g_transit[9][j] = 9;

	for (j = '0'; j <= '9'; j++)
		g_transit[14][j] = 6;
}
