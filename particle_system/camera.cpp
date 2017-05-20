#include "camera.h"

using namespace glm;

float turningDegree = -1.57079633f;


/* 
  Camera setup function.
  This creates the camera or view matrix based on the position of the player and the camera type.
  In this case, this we are going to create a first person camera.

  note: the lookAt function from GLM works the same as the *old* gluLookAt function
*/

void setupCamera(void)
{
  vec3 cameraPosition;

  //Define the view direction based on the camera's position
  cameraView.x = cameraPos.x + cos(angle);
  cameraView.y = cameraPos.y;
  cameraView.z = cameraPos.z + sin(angle);

  switch(camera_mode) {
  case 0:
    //Creates the view matrix based on the position, the view direction and the up vector
    cameraMatrix = lookAt(cameraPos, cameraView, cameraUp);
    break;
  case 1:
    cameraPosition = vec3(
      camera_particle->pos.x + cos(turningDegree),
      camera_particle->pos.y,
      camera_particle->pos.z + sin(turningDegree));

    cameraMatrix = lookAt(cameraPosition + camera_particle->dir, camera_particle->pos + camera_particle->dir, cameraUp);
    break;
  case 2: 
    camera_curve->setT(camera_curve->getT()+0.0001f);
    cameraMatrix = lookAt(camera_curve->p(), camera_curve->p(camera_curve->getT()+0.01f), cameraUp);
    break;

  case 3:
    cameraMatrix = lookAt(cameraPosition, camera_particle->pos, cameraUp);
    break;
  }
}
