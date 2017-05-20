#ifndef _ERRORINFO_INC
#define _ERRORINFO_INC

#include <Gl/glew.h>
#include <stdio.h>

/* 
  Error checking function:

  It checks for error in the OpenGL pipeline;
*/
void checkError(const char *functionName);

/*
  Prints the information regarding the OpenGL context
*/
void dumpInfo(void);

#endif
