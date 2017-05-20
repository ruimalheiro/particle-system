#include <math.h>
#include <stdlib.h>

#include "fieldoperations.h"
#include "defs.h"
#include "auxfuncs.h"

#define RANDP RAND(80.0f)

using namespace glm;

glm::vec3 earthPosition(60.0f, 0.0f, 0.0f);
glm::vec3 implodeFieldPosition(0.0f, 0.0f, 0.0f);

void newFrameField(void)
{
  earthPosition=resultField(earthPosition);


  if(demo_mode) {
    switch(demo_frame) {
    case 0:
      restart();
      mouse_state=1;
      break;
    case 100:
      camera_mode=0;
      selectedField=0;
      mouse_state=0;
      break;
    case 300:
      selectedField=5;
      break;
    case 450:
      camera_mode=2;

      camera_curve = new Bezier(
        glm::vec3(-34.335999, -12.976000, -34.416000),
        glm::vec3(-9.712000, -21.568001, 30.823999),
        glm::vec3(11.168000, 27.992001, 18.672001),
        glm::vec3(11.168000, 27.992001, 18.672001)
        );
      break;
    case 570:
      camera_mode=2;

      camera_curve = new Bezier(
        glm::vec3(-3.792000, 32.736000, 20.944000),
        glm::vec3(-9.248000, -3.208000, -26.351999),
        glm::vec3(-15.704000, 17.312000, -34.096001),
        glm::vec3(23.944000, 33.256001, -18.143999)
        );
      break;
    case 690:
      camera_mode=2;

      camera_curve = new Bezier(
        glm::vec3(-30.743999, -12.000000, 36.751999),
        glm::vec3(23.896000, -25.840000, -32.312000),
        glm::vec3(13.024000, 18.208000, -10.168000),
        glm::vec3(-17.912001, -39.799999, 11.824000)
        );
      break;
    case 810:
      camera_mode=2;

      camera_curve = new Bezier(
        glm::vec3(24.375999, 38.223999, 37.903999),
        glm::vec3(-32.608002, 3.384000, -25.351999),
        glm::vec3(3.776000, -36.088001, -25.864000),
        glm::vec3(-39.896000, 10.976000, 0.208000)
        );
      break;
    case 950:
      selectedField=11;
      break;
    case 1000:
      camera_mode=0;
      break;
    case 1012:
      mouse_state=1;
      break;
    case 1033:
      mouse_state=0;
      selectedField=7;
      break;
    case 1095:
      selectedField=8;
      break;
    case 1120:
      selectedField=11;
      break;
    case 1400:
      mouse_state=1;
      break;
    case 1414:
      mouse_state=0;
      break;
    case 1466:
      selectedField = 17;
      break;
    }
    demo_frame++;
  }
}

void moveImplodeField(int x, int y) {
  implodeFieldPosition.x += (float)x/10.0f;
  implodeFieldPosition.y = cameraPos.y;
  implodeFieldPosition.z += (float)y/10.0f;
}

glm::vec3 resultField(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;

  vec3 r;

  switch(selectedField) {
  case 0:
    r = 0.001f * (createField_6(p) * 0.5f + createField_3(p) * 0.5f);
    break;
  case 1:
    r = 0.001f * (createField_6(p));
    break;
  case 2:
    r = 0.001f * (createField_3(p));
    break;
  case 3:
    r = 0.001f * (createField_1(p));
    break;
  case 4:
    r = 0.001f * (createField_2(p));
    break;
  case 5:
    r = 0.001f * (createField_1(p) * 0.5f + createField_2(p) * 0.5f);
    break;
  case 6:
    r = 0.001f * (createField_7(p));
    break;
  case 7:
    r = 0.001f * (createField_13(p));
    break;
  case 8:
    r = 0.001f * (createField_12(p));
    break;
  case 9:
    r = 0.001f * (createField_12(p) * 0.5f + createField_4(p) * 0.5f);
    break;
  case 10:
    r = 0.01f * (createField_12(p) * 0.5f + createField_13(p) * 0.5f);
    break;  
  case 11:
    r = 0.01f * (createField_4(p));
    break;
  case 12:
    r = 0.01f * (createField_5(p));
    break;
  case 13:
    r = 0.01f * (createField_9(p));
    break;
  case 14:
    r = 0.01f * (createField_8(p));
    break;
  case 15:
    r = 0.01f * (createField_10(p));
    break;
  case 16:
    r = 0.01f * (createField_12(p));
    break;
  case 17:
    r = 0.01f * createField_Center(p);
  }

  if(mouse_state==2)
    return -r;
  return r*0.8f;
}

glm::vec3 createField_Center(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;

  if(x < 30.0f && x > -30.0f &&
    y < 30.0f && y > -30.0f &&
    z < 30.0f && z > -30.0f)
    return 0.1f * createField_12(p);

  return 0.1f * (
    glm::vec3(-x,-y,-z) 
    );
}

glm::vec3 moveMoon(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;

  return    0.001f * (
    vec3(-z, 0.0f, x) 
    ) + earthPosition;
}


// Ramdom fields

// { x,y }
glm::vec3 createField_1(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(x,y,z) 
    );
}

// { y,x }
glm::vec3 createField_2(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(y,x,z) 
    );
}

// { -y,x }
glm::vec3 createField_3(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(-y,x,z) 
    );
}

// { -x,-y }
glm::vec3 createField_4(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(-x,-y,-z) 
    );
}

// { (sin^2(x) + y) , cos(x+y^2) }
glm::vec3 createField_5(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(pow(sin(x),2)+y, cos(x+pow(y,2)), 0.0f) 
    );
}

// { (x/sqrt(x^2+y^2) , y/sqrt(x^2+y^2) }
glm::vec3 createField_6(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(x/sqrt(pow(x,2)+pow(y,2)), y/sqrt(pow(x,2)+pow(y,2)), 0.0f) 
    );
}

// { sin((3*x) + cos(3*y)), cos((3*x) + sin(3*y)) }
glm::vec3 createField_7(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(sin((3*x)+cos(3*y)), cos((3*x)+sin(3*y)), z) 
    );
}

// { 1, sin( (x^2 + y^2) }
glm::vec3 createField_8(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(1, sin(pow(x,2) + pow(y,2)), z) 
    );
}

// { cos(x^2+y), x-y^2+1 }
glm::vec3 createField_9(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(cos(pow(x,2)+y), x-pow(y,2)+1 , z) 
    );
}

// { x-y, x+y, 2z }
glm::vec3 createField_10(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(x-y, x+y , 2*z) 
    );
}

// { -x, -y, 2z }
glm::vec3 createField_11(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(-x, -y , 2*z) 
    );
}

// { yz, xz, 0 }
glm::vec3 createField_12(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(y*z, x*z , z*z) 
    );
}

// { -yz, xz, 0 }
glm::vec3 createField_13(glm::vec3 p)
{
  GLfloat x = p.x;
  GLfloat y = p.y;
  GLfloat z = p.z;
  return 0.1f * (
    glm::vec3(-y*z, x*z , 0.0f) 
    );
}
