#ifndef _MODEL_INC
#define _MODEL_INC

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "defs.h"
#include "objloader.h"

extern GLuint programId;
extern GLuint baseTextureId;

extern unsigned int demo_frame;

class Model {
public:
  std::string name;

  // Object
  GLuint vao;
  OBJLoader *object;

  // Textures
  GLuint baseTextureId;
  GLuint specularTextureId;

  // Position
  glm::vec3 pos;
  GLfloat speed;
  glm::vec3 dir;

public:
  Model() {}

  Model(GLuint vao, OBJLoader *object) :
    vao(vao), object(object)
  {
    this->newValues();
  }

  Model(GLuint vao, OBJLoader *object, glm::vec3 pos, GLfloat speed) :
    vao(vao), object(object), pos(pos), speed(speed)
  {}

  void newValues();
  void draw();
};

class Particle: public Model {
public:
  static OBJLoader *particleObject;
  static GLuint vao_particle;

  Particle(): Model(Particle::vao_particle, Particle::particleObject)
  {}

  Particle(glm::vec3 pos): Model(Particle::vao_particle, Particle::particleObject, pos, 1.0f)
  {}

  Particle(glm::vec3 pos, GLfloat speed): Model(Particle::vao_particle, Particle::particleObject, pos, speed)
  {}

  static void init();
  static void initGeometry();
  void moveField(glm::vec3 vector);
};

#endif /* _MODEL_INC */
