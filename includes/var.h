#ifndef VAR_H
# define VAR_H

/* 
** change the window size
** recommended value :
** SCREENX 1400
** SCREENY 900
*/

# define SCREENX 1400
# define SCREENY 900
# define RESOLUTION SCREENX * SCREENY

/*
** change the camera focal
** recommended value : FOV 10
*/

# define FOV 10

/*
** change the calculation accuracy of pixels
** recommended value : SAMPLE_RATE 4
** WARNING : calculation time is multiplied by SAMPLE_RATE
*/

# define SAMPLE_RATE 1

/*
** change the pixel per unit
** recommended value : PIXPERUNIT 1
*/

# define PIXPERUNIT 1

/*
** change the maximal distance to print object in the scene
** recommended value : MAX_DIST_TO_PRINT 15000
*/

# define MAX_DIST_TO_PRINT 15000

# endif
