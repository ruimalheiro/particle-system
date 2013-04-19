#ifndef _INIT_INC
#define _INIT_INC

#include <Gl/glew.h>
#include <FreeImage.h>

#include "errorinfo.h"
#include "shader.h"
#include "model.h"
#include "objloader.h"

extern GLuint vao;
extern GLuint geomId;
extern GLuint normalsId;
extern GLuint texUVId;

extern OBJLoader object;
extern GLuint baseTextureId;

extern Particle **particles;
/*
	Geometry initialization routine.

	1. Generate a VAO that holds that matchs the *ATTRIBUTES* (vertex position, normal, etc) to vertex buffer objects (VBO)(which hold the actual information)
	2. Active the VAO
	3. Active attribute 0 (first attribute in the vertex shader)
	4. Generate the VBO
	5. Activate the VBO
	6. Assign the geometry (the vertices variable previously defined) to the VBO (copying it to the graphics card's memory)
	7. Assign this VBO to the attribute
	8. Repeat steps 3-7 for remaining attributes
	9. Reset OpenGL's state
*/
void initGeometry();

GLuint loadTexture(char* textureFile);

/*
	Initialization function

	All initialization procedures should be performed here.
*/
void init(void);


#endif /* _INIT_INC */
