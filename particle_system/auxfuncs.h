#ifndef _AUXFUNCS_INC
#define _AUXFUNCS_INC

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "errorinfo.h"
#include "fieldoperations.h"
#include "defs.h"
#include "model.h"
#include "bezier.h"

extern glm::mat4 perspectiveMatrix;
extern glm::vec3 cameraPos;

extern float angle;
extern float velocity;

extern bool demo_mode;
extern unsigned int demo_frame;


/*
	Mouse state
	0 nothing
	1 down
	2 up 
*/
extern int mouse_state;

extern Particle **particles;
extern int selectedField;
extern int camera_mode;

extern Bezier *camera_curve;
extern Particle *camera_particle;

/*
	[FREEGLUT]
	This function is called whenever the user changes the size of the display window;

	The size of the OpenGL's viewport is mapped to the same size of the window.
*/
void reshape (int w, int h);

/*
	[FREEGLUT]
	Keyboard handling function
*/

void keyboard(unsigned char key, int x, int y);

/*
	[FREEGLUT]
	Special keys handling function (for "normal" keys, use the previously defined function)

	This function not only handles the special keys, but also controls the camera's position and rotation angle based on the input.	
*/
void keyboardSpecialKeys(int key, int x, int y);

void glutMouse(int button, int state, int x, int y);

void glutMotion(int x, int y);
void glutPassiveMotion(int x, int y);

void restart();

#endif
