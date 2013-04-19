#include "shader.h"

/*
	creates the program
	1. Generate the program's id
	2. Attach shader
	3. Repeat 2. until all shaders attached
	4. Link the program
	5. Check for errors

*/

void createAndCompileProgram(GLuint vertexId, GLuint fragId, GLuint *programId)
{
	*programId = glCreateProgram(); //1.
	glAttachShader(*programId, vertexId); //2. Attach the shader vertexId to the program programId
	glAttachShader(*programId, fragId); //2. Attach the shader fragId to the program programId

	glLinkProgram (*programId);//4.

	//5. Until the end of the if clause, is to check for COMPILE errors, and only for these. *not* related with the checkError procedure
	GLint status;
	glGetProgramiv (*programId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		char *infoLog;
		glGetProgramiv (*programId, GL_INFO_LOG_LENGTH, &infoLogLength);
		infoLog = new char[infoLogLength];
		glGetProgramInfoLog (*programId, infoLogLength, NULL, infoLog);
		fprintf (stderr, "link log: %s\n", infoLog);
		delete [] infoLog;
	}
	checkError ("createAndCompileProgram");
}

/*
	creates the shader in OpenGL and compiles it.

	1. Generate the shader id
	2. Set the shader's source
	3. Compile the shader
	4. Check for errors
*/

void createAndCompileShader(GLuint* id, GLenum type, GLsizei count, const char **shaderSource)
{
	*id = glCreateShader(type); //1. create the shader with type. (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER. others will follow in the future)

	glShaderSource(*id, count, shaderSource, NULL); //2. the shader's source. *id: shader's id; count: memory size of the contents; shaderSource: shader contents; NULL ;)

	glCompileShader(*id); //3.

	//4. Until the end of the if clause, is to check for COMPILE errors, and only for these. *not* related with the checkError procedure
	GLint status;
	glGetShaderiv (*id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		char *infoLog;
		glGetShaderiv (*id, GL_INFO_LOG_LENGTH, &infoLogLength);
		infoLog = new char[infoLogLength];
		glGetShaderInfoLog (*id, infoLogLength, NULL, infoLog);
		fprintf (stderr, "compile log: %s\n", infoLog);
		delete [] infoLog;
	}

	checkError ("createAndCompileShader");

}
/*
	loads the shader in file.
	1. load the file from disk into a memory block
	2. create the shader

*/

void loadShader (char *file, GLuint *id, GLenum type) 
{
	//Open e load  shader file
	FILE* f = fopen(file, "r");
	if (!f) {
		fprintf(stderr, "Unable to open shader file: %s", file);
		return;
	}

	fseek(f, 0, SEEK_END);

	int fileSize = ftell(f);
	rewind(f);

	char *fileContents = new char[fileSize];
	memset(fileContents, 0, fileSize);
	fread(fileContents, sizeof(char), fileSize, f);
	//up until here is to load the contents of the file

	const char* t = fileContents;

	//2. create the shader. arguments (future) shader id, type of shader, memory size of the file contents, file contents
	createAndCompileShader(id, type, sizeof(fileContents)/sizeof(char*), &t);

	//cleanup
	fclose(f);
	delete [] fileContents;
}
/*
	loads two shader files, one vertex shader and one fragment shader, and creates the program.
	the arguments are the path to the files, including file name.
*/

void loadShaderProgram(char* vertexFile, char* fragmentFile)
{
	//load each shader seperately. arguments: the file, (future) shader id, shader type

	loadShader(vertexFile, &vertexShaderId, GL_VERTEX_SHADER); 
	loadShader(fragmentFile, &fragShaderId, GL_FRAGMENT_SHADER);

	//one the shaders loaded, create the program with the two shaders. arguments: vertex shader id, fragment shader id, (future) program id
	createAndCompileProgram(vertexShaderId, fragShaderId, &programId);
}
