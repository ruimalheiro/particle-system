#include "errorinfo.h"

/* 
  Error checking function:

  It checks for error in the OpenGL pipeline;
*/

void checkError(const char *functionName)
{
  GLenum error;
  while (( error = glGetError() ) != GL_NO_ERROR) {
    fprintf (stderr, "GL error 0x%X detected in %s\n", error, functionName);
  }
}

/*
  Prints the information regarding the OpenGL context
*/

void dumpInfo(void)
{
  printf ("Vendor: %s\n", glGetString (GL_VENDOR));
  printf ("Renderer: %s\n", glGetString (GL_RENDERER));
  printf ("Version: %s\n", glGetString (GL_VERSION));
  printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
  checkError ("dumpInfo");
}
