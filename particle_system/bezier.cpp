#include "bezier.h"

Bezier::Bezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	this->points.push_back(p0);
	this->points.push_back(p1);
	this->points.push_back(p2);
	this->points.push_back(p3);
	this->n_segments=1;
	this->t = 0.0f;
}

void Bezier::add(glm::vec3 p2, glm::vec3 p3, GLfloat f)
{
	// p0
	glm::vec3 p0(this->points[this->points.size()-1]);
	this->points.push_back(p0);

	// p1
	glm::vec3 p1(this->points[this->points.size()-3]);
	p1 = (-(p1 - p0) + p0) * f;
	this->points.push_back(p1);

	// p2
	this->points.push_back(p2);

	// p3
	this->points.push_back(p3);

	this->n_segments++;

#ifdef _DEBUG_
	for(int i=0;i<this->points.size();i++)
		printf("(%f, %f, %f)\n",this->points[i].x,this->points[i].y,this->points[i].z);
#endif
}

glm::vec3 Bezier::p(GLfloat t)
{
	if(t>0.999f)
		t=0.999f;

	GLfloat seg_len = ((float)1/(float)this->n_segments);
	int segment = (int)(t/seg_len);
	t = (t - seg_len * segment) / seg_len;

#ifdef _DEBUG_
	printf("SegLen: %f  Segment: %d  t: %f\n",seg_len,segment,t);
#endif
	segment *= 4;

#ifdef _DEBUG_
	printf("p0 (%f, %f, %f)\n",this->points[segment+0].x,this->points[segment+0].y,this->points[segment+0].z);
	printf("p1 (%f, %f, %f)\n",this->points[segment+1].x,this->points[segment+1].y,this->points[segment+1].z);
	printf("p2 (%f, %f, %f)\n",this->points[segment+2].x,this->points[segment+2].y,this->points[segment+2].z);
	printf("p3 (%f, %f, %f)\n",this->points[segment+3].x,this->points[segment+3].y,this->points[segment+3].z);
#endif

	glm::vec3 p(
		CUBE((1-t)) * this->points[segment+0] +	// p0
		3 * t * QUAD(1-t) * this->points[segment+1] + // p1
		3 * QUAD(t) * (1-t) * this->points[segment+2] + // p2
		CUBE(t) * this->points[segment+3]); // p3

#ifdef _DEBUG_
	printf("(%f, %f, %f)\n",p.x,p.y,p.z);
#endif

	return p;
}

glm::vec3 Bezier::p()
{
	return this->p(this->t);
}

GLfloat Bezier::getT() {
	return this->t;
}
void Bezier::setT(GLfloat t) {
	if(t>1.0f)
		this->t = 1.0f;
	else
		this->t = t;
}

void Bezier::dump() {
	puts("Points:");
	for(unsigned int i=0;i<this->points.size();i++)
		printf("[%3d] ( %f, %f, %f)\n",i,this->points[i].x, this->points[i].y, this->points[i].z);
}
