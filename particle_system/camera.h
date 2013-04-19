#ifndef _CAMERA_INC
#define _CAMERA_INC

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "bezier.h"
#include "model.h"

extern glm::mat4 cameraMatrix;

extern glm::vec3 cameraPos;
extern glm::vec3 cameraView;
extern glm::vec3 cameraUp;

extern float angle;
extern int camera_mode;
extern Bezier *camera_curve;
extern Particle *camera_particle;

/* 
	Camera setup function.
	This creates the camera or view matrix based on the position of the player and the camera type.
	In this case, this we are going to create a first person camera.

	note: the lookAt function from GLM works the same as the *old* gluLookAt function
*/

void setupCamera(void);

#endif /* _CAMERA_INC */
