#include <stdio.h>
#include <time.h>
#include <string.h>

#include <Gl/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "defs.h"
#include "errorinfo.h"
#include "shader.h"
#include "camera.h"
#include "auxfuncs.h"
#include "init.h"
#include "display.h"
#include "model.h"
#include "bezier.h"

#include "objloader.h"

bool inited = false; //Have we done initialization?

/*
	vao: will hold the VAO identifier (usually one per object)
	geomId: will hold the VBO identifier (one per attribute: position, normal, etc.)
*/

GLuint vao;
GLuint geomId;
GLuint normalsId;
GLuint texUVId;

/*
	variables to hold the shaders related identifiers

	vertexShaderId: will hold the vertex shader identifier
	fragShaderId: will hold the fragment shader identifier
	programId: will hold the program identifier
*/

GLuint vertexShaderId;
GLuint fragShaderId;
GLuint programId;

GLuint baseTextureId;
GLuint specularTextureId;

/*
	Perspective and camera related variables.

	perspectiveMatrix: perspective matrix. this is a GLM type, representing a 4x4 matrix
	cameraMatrix: camera or view matrix.
	cameraPos: camera initial position
	cameraView: camera view direction
	cameraUp: camera up vector
	angle: initial viewing angle (-PI/2)
	velocity: camera's rotation and moving velocity

*/
int camera_mode = 0;
Bezier *camera_curve;
Particle *camera_particle;

glm::mat4 perspectiveMatrix;
glm::mat4 cameraMatrix;

glm::vec3 cameraPos(0.0f, 0.0f, 80.0f);
glm::vec3 cameraView(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

float angle = -1.57079633f;

float velocity = 1.0f;


GLfloat lightDir[] = {1.0f, 1.0f, 1.0};
GLfloat lightIntensity[] = {0.9f, 0.9f, 0.9f, 1.0f};

GLfloat ambientComponent[] = {0.4f, 0.4f, 0.4f, 1.0f};
GLfloat diffuseColor[] = {1.0f, 1.0f, 1.0f, 1.0f};

OBJLoader object("../models/particle.obj");

Particle **particles;

/* 
	Mouse state
	0 nothing
	1 down
	2 up 
*/
int mouse_state = 0;

int selectedField = 0;

bool demo_mode = false;
unsigned int demo_frame = 0;

struct PARAMS params;

/* 
	This is a function to be issued on every cycle.

	It performs all that is needed for an interactive simulation.
*/

void mainLoop(void)
{
	setupCamera();
	display();
}

#define CPARAM(x)	if(strcmp(argv[i],(x))==0)

void parse_params(char **argv) {

	// Default values
	params.demo = false;
	params.fullscreen = false;
	params.res_width = 1024;
	params.res_height = 768;
	params.obj = "../models/sphere.obj";
	params.texture = "../models/sun.jpg";
	params.particles = 20000;

	for(int i=1; argv[i]!=NULL;i++) {
		CPARAM("-d")
			params.demo = true;
		CPARAM("-f")
			params.fullscreen = true;
		CPARAM("-r") {
			params.res_width = atoi(argv[++i]);
			params.res_height = atoi(argv[++i]);
		}
		CPARAM("-t")
			params.texture = argv[++i];
		CPARAM("-o")
			params.obj = argv[++i];
		CPARAM("-p")
			params.particles = atoi(argv[++i]);
		CPARAM("-h") {
			printf("Usage: %s [-d] [-f] [-r w h] [-t file] [-o file] [-p #particles] [-h]\n",argv[0]);
			puts("Options");
			puts("  -d\tautostart demo");
			puts("  -f\tfullscreen");
			puts("  -h\thelp");
			puts("  -o\tobject model file (obj format) - default: \"../models/sphere.obj\"");
			puts("  -p\tnumber of particles - default: 50000");
			puts("  -r\tresolution [width x height] - default: 1024x768");
			puts("  -t\ttexture file - default: \"../models/sun.jpg\"");
			exit(0);
		}
	}
}

int main(int argc, char** argv)
{
	parse_params(argv);

	srand((unsigned int)time(NULL));
	particles = new Particle* [N_PARTICLES];

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //Double buffer; Color display

	glutInitContextVersion(3, 3); //OpenGL 3.3
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG); //Forward compatible profile (Old Opengl (pre-3.x) functions can be used, but SHOULDN'T) 

	glutInitWindowSize(params.res_width, params.res_height);
	glutCreateWindow(argv[0]);

	if(params.fullscreen)
		glutFullScreen();

	dumpInfo();

	/*
		Sets the specific functions
	*/
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecialKeys);
	glutMouseFunc(glutMouse);
	glutMotionFunc(glutMotion);
	glutPassiveMotionFunc(glutPassiveMotion);
	glutIdleFunc(mainLoop);

	checkError ("main");
	glutMainLoop(); //starts processing


	return 0;
}
