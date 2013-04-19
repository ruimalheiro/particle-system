#include "init.h"

GLuint sunTexture;

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

void initGeometry()
{
	const float *vertices = object.getVerticesArray();
	const float *textureCoords = object.getTextureCoordinatesArray();
	const float *normals = object.getNormalsArray();

	// Object geometry
	glGenVertexArrays(1, &vao); //1.
	glBindVertexArray(vao); //2.
	glEnableVertexAttribArray(0); //3.
	glGenBuffers(1, &geomId); //4.
	glBindBuffer(GL_ARRAY_BUFFER, geomId); //5.
	glBufferData(GL_ARRAY_BUFFER, object.getNVertices() * 3 * sizeof(float), vertices, GL_STATIC_DRAW); //6. GL_ARRAY_BUFFER: the type of buffer; sizeof(vertices): the memory size; vertices: the pointer to data; GL_STATIC_DRAW: data will remain on the graphics card's memory and will not be changed
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //7. 0: the *ATTRIBUTE* number; 3: the number of coordinates; GL_FLOAT: the type of data; GL_FALSE: is the data normalized? (usually it isn't), 0: stride (forget for now); 0: data position (forget for now)

	// Object coordinates
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &texUVId);
	glBindBuffer(GL_ARRAY_BUFFER, texUVId);
	glBufferData(GL_ARRAY_BUFFER, object.getNVertices() * 2 * sizeof(float), textureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Object normals
	glEnableVertexAttribArray(2);
	glGenBuffers(1, &normalsId);
	glBindBuffer(GL_ARRAY_BUFFER, normalsId);
	glBufferData(GL_ARRAY_BUFFER, object.getNVertices() * 3 * sizeof(float), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Particles
	Particle::initGeometry();
	for(int i=0; i<N_PARTICLES; i++)
		particles[i] = new Particle();

	checkError("initBuffer");
	glBindBuffer(GL_ARRAY_BUFFER, 0); //9.
	glBindVertexArray(0); //9.
}


GLuint loadTexture(char* textureFile)
{
	GLuint tId;

	FIBITMAP *tf = FreeImage_Load(FIF_JPEG, textureFile);
	if (tf) {

		fprintf(stderr, "Texture: %s loaded\n", textureFile);

		glGenTextures(1, &tId);
		glBindTexture(GL_TEXTURE_2D, tId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FreeImage_GetWidth(tf), FreeImage_GetHeight(tf), 0, GL_BGR, GL_UNSIGNED_BYTE, FreeImage_GetBits(tf));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		checkError("loadTexture");
		glBindTexture(GL_TEXTURE_2D, 0);

		FreeImage_Unload(tf);

		return tId;
	}
	return 0;
}

/*
	Initialization function

	All initialization procedures should be performed here.
*/

void init(void) 
{

	/*
		GLEW initialization.
		activate GLEW experimental features to have access to the most recent OpenGL, and then call glewInit.
		it is important to know that this must be done only when a OpenGL context already exists, meaning, in this case, glutCreateWindow has already been called.

	*/

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err != GLEW_OK) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
	} else {
		if (GLEW_VERSION_3_3)
		{
			fprintf(stderr, "Driver supports OpenGL 3.3\n");
		}
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	FreeImage_Initialise();

	loadShaderProgram("../shaders/vertex_shader.vs", "../shaders/frag_shader.fs");

	baseTextureId = loadTexture(params.texture);

	object.init();
	Particle::init();
	initGeometry();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Defines the clear color, i.e., the color used to wipe the display
	glEnable(GL_DEPTH_TEST);
	checkError("init");
}
