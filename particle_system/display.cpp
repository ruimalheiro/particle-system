#include "display.h"
#include "fieldoperations.h"
#include <time.h>

time_t time_before;
unsigned int frame_count;

/*
	[FREEGLUT]

	display function;
	This function is called to paint the display. This is where the drawing functions should be placed.
	Why is the init inside display? Because some drivers require that the display window to be visible to work correctly; therefore, the initialization is done once, but on the first call to 
	display, ensuring that the window is visible;
*/
void display(void)
{
	if (!inited) {
		time_before = time(NULL);
		frame_count = 0;
		demo_mode = params.demo;

		init();
		inited = true;
	}


	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the display with the defined clear color
	glUseProgram(programId);

	// Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, baseTextureId);

	GLuint loc = glGetUniformLocation(programId, "tex");
	glUniform1i(loc, 0); 

	// Perspective Matrix
	loc = glGetUniformLocation(programId, "pMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat *)&perspectiveMatrix[0]);

	// Camera Matrix
	loc = glGetUniformLocation(programId, "vMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat *)&cameraMatrix[0]);

	// Model Matrix
	loc = glGetUniformLocation(programId, "mMatrix");

	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)); 

	glm::mat4 model = translateMatrix * rotateY;
	glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat *)&model[0]);

	// Ilumination	
	//glm::mat4 cameraModelMatrix = cameraMatrix * model; // Camera Model Matrix

	loc = glGetUniformLocation(programId, "nMatrix");
	glm::mat3 normalMatrix = glm::mat3(cameraMatrix);
	glUniformMatrix3fv(loc, 1, GL_FALSE, (GLfloat *)&normalMatrix[0]);

	/*
	if using non-uniform scaling:

	glm::mat4 cameraModelMatrix = cameraMatrix * model;
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(cameraModelMatrix)));
	*/


	loc = glGetUniformLocation(programId, "lightDir");
	glm::vec4 transformedLightDir = cameraMatrix * glm::vec4(lightDir[0], lightDir[1], lightDir[2], 0.0f);
	glUniform3fv(loc, 1, (GLfloat *)&transformedLightDir[0]);


	loc = glGetUniformLocation(programId, "lightIntensity");
	glUniform4fv(loc, 1, lightIntensity);


	loc = glGetUniformLocation(programId, "ambientIntensity");
	glUniform4fv(loc, 1, ambientComponent);


	loc = glGetUniformLocation(programId, "diffuseColor");
	glUniform4fv(loc, 1, diffuseColor);

	// End ilumination.

	glBindVertexArray(vao);
	const unsigned int *indices = object.getIndicesArray();

	newFrameField();
	for(int i=0;i<N_PARTICLES;i++) {
		if(mouse_state==1)
			particles[i]->dir *= 0.8f;
		else
			particles[i]->moveField(resultField(particles[i]->pos));
		particles[i]->draw();
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0); //4.
	glUseProgram(0); //4.

	frame_count++;
	if(time_before != time(NULL)) {
		printf("\b\b\b\b\b\b\b%3d fps",frame_count);

		time_before = time(NULL);
		frame_count = 0;
	}

	glFlush(); //Instructes OpenGL to finish all rendering operations
	glutSwapBuffers(); //Swaps the display in a double buffering scenario. In double buffering, rendering is done in a offline buffer (not directly on the screen); this avoid flickering 
	checkError ("display");
}
