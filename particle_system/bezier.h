#ifndef _BEZIER_INC
#define _BEZIER_INC

#include <Gl/glew.h>
#include <glm/glm.hpp>
#include <vector>

#define QUAD(x)	(x)*(x)
#define CUBE(x) QUAD(x)*(x)

class Bezier {
private:
	std::vector<glm::vec3> points;
	int n_segments;
	GLfloat t;

public:
	Bezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

	void add(glm::vec3 p2, glm::vec3 p3, GLfloat f);

	glm::vec3 p(GLfloat t);
	glm::vec3 p();

	GLfloat getT();
	void setT(GLfloat t);

	void dump();
};

#endif
