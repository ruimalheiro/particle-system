#ifndef _DISPLAY_INC
#define _DISPLAY_INC

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "init.h"

extern bool inited;

extern glm::mat4 perspectiveMatrix;
extern glm::mat4 cameraMatrix;

extern GLfloat lightDir[];
extern GLfloat lightIntensity[];

extern GLfloat ambientComponent[];
extern GLfloat diffuseColor[];

/*
  [FREEGLUT]

  display function;
  This function is called to paint the display. This is where the drawing functions should be placed.
  Why is the init inside display? Because some drivers require that the display window to be visible to work correctly; therefore, the initialization is done once, but on the first call to 
  display, ensuring that the window is visible;
*/
void display(void);

#endif /* _DISPLAY_INC */
