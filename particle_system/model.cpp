#include "model.h"


/************************
* Model
*/

void Model::draw() {
  this->pos += this->dir;

  GLuint loc = glGetUniformLocation(programId, "mMatrix");

  glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), this->pos);
  glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat *)&translateMatrix[0]);

  // Draw
  glBindVertexArray(vao);

  const unsigned int *indices = object->getIndicesArray();

  glDrawElements(GL_TRIANGLES, object->getNIndices(), GL_UNSIGNED_INT, indices); //type of geometry; number of indices; type of indices array, indices pointer

}


/************************
* Particle
*/

GLuint Particle::vao_particle = 0;
OBJLoader* Particle::particleObject = new OBJLoader();

void Particle::init() {
  Particle::particleObject->setFile(params.obj);
  Particle::particleObject->init();
}

void Particle::initGeometry() {
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
  GLuint geomId_particle, texUVId_particle, normalsId_particle;
  const float *vertices = Particle::particleObject->getVerticesArray();
  const float *textureCoords = Particle::particleObject->getTextureCoordinatesArray();
  const float *normals = Particle::particleObject->getNormalsArray();

  // Particle geometry
  glGenVertexArrays(1, &Particle::vao_particle); //1.
  glBindVertexArray(Particle::vao_particle); //2.
  glEnableVertexAttribArray(0); //3.
  glGenBuffers(1, &geomId_particle); //4.
  glBindBuffer(GL_ARRAY_BUFFER, geomId_particle); //5.
  glBufferData(GL_ARRAY_BUFFER, Particle::particleObject->getNVertices() * 3 * sizeof(float), vertices, GL_STATIC_DRAW); //6. GL_ARRAY_BUFFER: the type of buffer; sizeof(vertices): the memory size; vertices: the pointer to data; GL_STATIC_DRAW: data will remain on the graphics card's memory and will not be changed
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //7. 0: the *ATTRIBUTE* number; 3: the number of coordinates; GL_FLOAT: the type of data; GL_FALSE: is the data normalized? (usually it isn't), 0: stride (forget for now); 0: data position (forget for now)

  // Particle texture coordinates
  glEnableVertexAttribArray(1);
  glGenBuffers(1, &texUVId_particle);
  glBindBuffer(GL_ARRAY_BUFFER, texUVId_particle);
  glBufferData(GL_ARRAY_BUFFER, Particle::particleObject->getNVertices() * 2 * sizeof(float), textureCoords, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  // Particle normals
  glEnableVertexAttribArray(2);
  glGenBuffers(1, &normalsId_particle);
  glBindBuffer(GL_ARRAY_BUFFER, normalsId_particle);
  glBufferData(GL_ARRAY_BUFFER, Particle::particleObject->getNVertices() * 3 * sizeof(float), normals, GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Particle::moveField(glm::vec3 vector) {
  this->dir += vector;
}

void Model::newValues() {
  GLfloat x, y, z, r, phi, theta;
  const float ray = 30.0f;

  theta = ((float)(rand()%10000)/(float)10000) * 2 * PI - PI;
  phi = ((float)(rand()%10000)/(float)10000) * 2 * PI - PI;
  r = ((float)(rand()%10000)/(float)10000) * ray - ray/2;
  x = r*cos(theta)*cos(phi);
  y = r*cos(theta)*sin(phi);
  z = r*sin(theta);
  this->pos = glm::vec3(x, y, z);

  this->speed = 1.0f; //((float)(rand()%1000)/(float)1000);
  this->dir = glm::vec3(0.0f, 0.0f, 0.0f);
}
