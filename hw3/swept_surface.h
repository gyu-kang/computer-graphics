#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "glm-0.9.7.4/glm/glm.hpp"
#include "glm-0.9.7.4/glm/gtc/type_ptr.hpp"
#include "glm-0.9.7.4/glm/gtc/matrix_transform.hpp"
#include "glm-0.9.7.4/glm/gtx/rotate_vector.hpp"
#include "glm-0.9.7.4/glm/gtc/matrix_inverse.hpp"
#include "glm-0.9.7.4/glm/gtx/vector_angle.hpp"
#include "glm-0.9.7.4/glm/gtx/transform.hpp"

#include "mesh.h"
#include "data.h"
#include "trackball.h"

const int STEPS = 5;

static inline int circularIndex(int size, int index) {
  if (index < -size) return (size + index % size) % size;
  else if (index < 0) return size + index;
  else if (index >= size) return (index - size) % size;
  else return index;
}

static inline float bSplinePolynomial(float *U, float *G) {
  return ((-1.0f * U[0] + 3.0f * U[1] - 3.0f * U[2] + 1.0f) * G[0]
    + (3.0f * U[0] - 6.0f * U[1] + 0.0f + 4.0f) * G[1]
    + (-3.0f * U[0] + 3.0f * U[1] + 3.0f * U[2] + 1.0f) * G[2]
    + (1.0f * U[0] + 0.0f + 0.0f + 0.0f) * G[3]) / 6.0f;
}

static inline float catmullRomSplinePolynomial(float *U, float *G) {
  return ((-1.0f * U[0] + 2.0f * U[1] - 1.0f * U[2] + 0.0f) * G[0]
    + (3.0f * U[0] - 5.0f * U[1] + 0.0f + 2.0f) * G[1]
    + (-3.0f * U[0] + 4.0f * U[1] + 1.0f * U[2] + 0.0f) * G[2]
    + (1.0f * U[0] - 1.0f * U[1] + 0.0f + 0.0f) * G[3]) / 2.0f;
}
