#pragma once
// Freeglut headers
#include "GL/freeglut.h"

// OpenGL headers
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <stdlib.h>
#include <math.h>