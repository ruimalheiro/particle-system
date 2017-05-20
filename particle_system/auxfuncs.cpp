#include "auxfuncs.h"

#define RANDP RAND(80.0f)

int prev_mouse_x, prev_mouse_y;

/*
  [FREEGLUT]
  This function is called whenever the user changes the size of the display window;

  The size of the OpenGL's viewport is mapped to the same size of the window.
*/

void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  /* 
    This sets the perspective matrix. There's no need to compute this matrix at each frame. Only when the window changes size
  */

  float aspect = (float)w/(float)h; //aspect ratio.

  perspectiveMatrix = glm::perspective(45.0f, aspect, 0.001f, 1000.0f); //field of view; aspect ratio; z near; z far;

  checkError ("reshape");
}

/*
  [FREEGLUT]
  Keyboard handling function
*/

void keyboard(unsigned char key, int x, int y)
{
  if(key==27) // Escape
    putchar('\n'), exit(0);
  if(key==13) { // Enter
    demo_mode=!demo_mode;
    demo_frame=0;
  }
  if(demo_mode)
    return;

  switch (key) {
  case 'A':
  case 'a':
    cameraPos.x += sin(angle) * velocity;
    cameraPos.z -= cos(angle) * velocity;
    break;
  case 'D':
  case 'd':
    cameraPos.x -= sin(angle) * velocity;
    cameraPos.z += cos(angle) * velocity;
    break;
  case 'W':
  case 'w':
    cameraPos.y += velocity;
    break;
  case 'S':
  case 's':
    cameraPos.y -= velocity;
    break;
  case 'R':
  case 'r':
    restart();
    break;


  case '0':
    selectedField = 10;
    break;
  case '1':
    selectedField = 0;
    break;
  case '2':
    selectedField = 1;
    break;
  case '3':
    selectedField = 2;
    break;
  case '4':
    selectedField = 3;
    break;
  case '5':
    selectedField = 4;
    break;
  case '6':
    selectedField = 5;
    break;
  case '7':
    selectedField = 6;
    break;
  case '8':
    selectedField = 7;
    break;
  case '9':
    selectedField = 8;
    break;
  case 'Z':
  case 'z':
    selectedField = 9;
    break;
  case 'X':
  case 'x':
    selectedField = 11;
    break;
  case 'C':
  case 'c':
    selectedField = 12;
    break;
  case 'V':
  case 'v':
    selectedField = 13;
    break;
  case 'B':
  case 'b':
    selectedField = 14;
    break;
  case 'N':
  case 'n':
    selectedField = 15;
    break;
  case 'M':
  case 'm':
    selectedField = 16;
    break;
  case 'L':
  case 'l':
    selectedField = 17;
    break;
  }
}

/*
  [FREEGLUT]
  Special keys handling function (for "normal" keys, use the previously defined function)

  This function not only handles the special keys, but also controls the camera's position and rotation angle based on the input. 
*/

void keyboardSpecialKeys(int key, int x, int y)
{
  if(key==GLUT_KEY_F11)
    glutFullScreenToggle();
  if(demo_mode)
    return;

  switch (key) {
  case GLUT_KEY_LEFT:
    angle -= velocity/8;
    break;
  case GLUT_KEY_RIGHT:
    angle += velocity/8;
    break;
  case GLUT_KEY_UP:
    cameraPos.x += cos(angle) * velocity;
    cameraPos.z += sin(angle) * velocity;
    break;
  case GLUT_KEY_DOWN:
    cameraPos.x -= cos(angle) * velocity;
    cameraPos.z -= sin(angle) * velocity;
    break;

  case GLUT_KEY_F1:
    camera_mode=0;
    break;
  case GLUT_KEY_F2:
    camera_mode=1;

    camera_particle = particles[rand()%N_PARTICLES];

    break;
  case GLUT_KEY_F3:
    camera_mode=2;

    camera_curve = new Bezier(
      glm::vec3(RANDP, RANDP, RANDP),
      glm::vec3(RANDP, RANDP, RANDP),
      glm::vec3(RANDP, RANDP, RANDP),
      glm::vec3(RANDP, RANDP, RANDP)
      );
    camera_curve->add(glm::vec3(RANDP, RANDP, RANDP), glm::vec3(RANDP, RANDP, RANDP), 1.0f);
    camera_curve->add(glm::vec3(RANDP, RANDP, RANDP), glm::vec3(RANDP, RANDP, RANDP), 1.0f);
    camera_curve->add(glm::vec3(RANDP, RANDP, RANDP), glm::vec3(RANDP, RANDP, RANDP), 1.0f);

    break;
  case GLUT_KEY_F4:
    camera_mode=3;

    camera_particle = particles[rand()%N_PARTICLES];

    break;
  }
}


void glutMouse(int button, int state, int x, int y) {
  if(demo_mode)
    return;

  switch(button) {
  case GLUT_LEFT_BUTTON:
    if(state==GLUT_DOWN)
      mouse_state = 1;
    else if(state==GLUT_UP)
      mouse_state = 0;
    break;
  case GLUT_MIDDLE_BUTTON:

    break;
  case GLUT_RIGHT_BUTTON:
    if(state==GLUT_DOWN)
      mouse_state = 2;
    else if(state==GLUT_UP)
      mouse_state = 0;
    break;
  }
}

void glutMotion(int x, int y) {
  moveImplodeField(x - prev_mouse_x, y - prev_mouse_y);
  prev_mouse_x = x;
  prev_mouse_y = y;
}

void glutPassiveMotion(int x, int y) {
  moveImplodeField(x - prev_mouse_x, y - prev_mouse_y);
  prev_mouse_x = x;
  prev_mouse_y = y;
}

void restart() {
  for(int i=0;i<N_PARTICLES;i++) {
    particles[i]->newValues();
  }
}
