#ifndef _FIELDOPERATIONS_INC
#define _FIELDOPERATIONS_INC

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "bezier.h"

extern int mouse_state;
extern glm::vec3 cameraPos;
extern int selectedField;
extern bool demo_mode;
extern unsigned int demo_frame;
extern int camera_mode;
extern int mouse_state;
extern Bezier *camera_curve;

void newFrameField(void);
void moveImplodeField(int x, int y);
glm::vec3 resultField(glm::vec3 p);

glm::vec3 crazyField(glm::vec3 p);
glm::vec3 moveMoon(glm::vec3 p);

glm::vec3 createField_1(glm::vec3 p);
glm::vec3 createField_2(glm::vec3 p);
glm::vec3 createField_3(glm::vec3 p);
glm::vec3 createField_4(glm::vec3 p);
glm::vec3 createField_5(glm::vec3 p);
glm::vec3 createField_6(glm::vec3 p);
glm::vec3 createField_7(glm::vec3 p);
glm::vec3 createField_8(glm::vec3 p);
glm::vec3 createField_9(glm::vec3 p);
glm::vec3 createField_10(glm::vec3 p);
glm::vec3 createField_11(glm::vec3 p);
glm::vec3 createField_12(glm::vec3 p);
glm::vec3 createField_13(glm::vec3 p);


glm::vec3 createField_Center(glm::vec3 p);

#endif