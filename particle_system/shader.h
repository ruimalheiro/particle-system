#ifndef _SHADER_INC
#define _SHADER_INC

#include <Gl/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

#include "errorinfo.h"

extern GLuint vertexShaderId;
extern GLuint fragShaderId;
extern GLuint programId;


/*
	creates the program
	1. Generate the program's id
	2. Attach shader
	3. Repeat 2. until all shaders attached
	4. Link the program
	5. Check for errors
*/
void createAndCompileProgram(GLuint vertexId, GLuint fragId, GLuint *programId);


/*
	creates the shader in OpenGL and compiles it.

	1. Generate the shader id
	2. Set the shader's source
	3. Compile the shader
	4. Check for errors
*/
void createAndCompileShader(GLuint* id, GLenum type, GLsizei count, const char **shaderSource);


/*
	loads the shader in file.
	1. load the file from disk into a memory block
	2. create the shader
*/
void loadShader (char *file, GLuint *id, GLenum type);

/*
	loads two shader files, one vertex shader and one fragment shader, and creates the program.
	the arguments are the path to the files, including file name.
*/
void loadShaderProgram(char* vertexFile, char* fragmentFile);

#endif
