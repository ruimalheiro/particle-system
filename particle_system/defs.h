#ifndef _DEFS_INC
#define _DEFS_INC

struct PARAMS {
  bool demo;
  bool fullscreen;
  int res_width, res_height;
  char *obj;
  char *texture;
  int particles;
};

extern struct PARAMS params;

#define N_PARTICLES (params.particles)
#define PI      3.14159265f


#define RAND(x) (((float)(rand()%10000)/(float)10000) * (x) - (x)/2)

#endif /* _DEFS_INC */